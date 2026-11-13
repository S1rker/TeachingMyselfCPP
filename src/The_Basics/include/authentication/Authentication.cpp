#include <SQLiteCpp/SQLiteCpp.h>
#include "Authentication.h"
#include "migrate.h"
#include <iostream>
#include "passwordHasher.h"

Authentication::Authentication()
    : m_db(DB_PATH, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE)
{ /* create table as above */
    m_db.exec("PRAGMA foreign_keys = ON");
    migrate(m_db, MIGRATIONS_DIR);
}

Authentication::~Authentication() = default;

bool Authentication::login(const std::string& user, const std::string& password)
{
    try{
        SQLite::Statement q(m_db, "SELECT password_hash FROM users WHERE username = ?");
        q.bind(1,user);
        if (!q.executeStep())
            return false;
        return PasswordHasher::verify(password, q.getColumn(0).getString());
    }
    catch (const SQLite::Exception& e) {
    std::cout << "insert failed: " << e.what() << " reg " << '\n';
    return false;
    }
    return false;
}

bool Authentication::loginCheck(const std::string& user, const std::string& password)
{
    /*
    this is going to go through the database and look for a username matching the ones
     given if there isn't one it return false else.
    */
    if (!userExists(user))
        return false;
    if (user.empty() || password.size() < 8) return false;
    return login(user, password);
}
bool Authentication::registration(const std::string& user, const std::string& password)
{
    try{
    SQLite::Transaction transaction(m_db);
    SQLite::Statement insert(m_db,
        "INSERT INTO users (username, password_hash) VALUES (?, ?)");
    insert.bind(1, user);
    insert.bind(2, PasswordHasher::hash(password));
    insert.exec();
    insert.reset();
    transaction.commit();
    return false;
    }
    catch (const SQLite::Exception& e) {
    std::cout << "insert failed: " << e.what() << " reg " << '\n';
    return true;
    }
}
bool Authentication::userExists(const std::string& user)
{
    try{
    SQLite::Statement q(m_db, "SELECT 1 FROM users WHERE username = ?");
    q.bind(1, user);
    return q.executeStep();
    }
    catch (const SQLite::Exception& e) {
    std::cout << "insert failed: " << e.what() << " userexist "<<'\n';
    return false;
    }
    
}
bool Authentication::regCheck(const std::string& user, const std::string& password)
{
    if (userExists(user))
        return true;
    if (user.empty() || password.size() < 8) return false;
    return registration(user, password);
}

std::vector<std::string> Authentication::roomBuild(const std::string& user)
{   
    std::vector<std::string> rooms;
    try {
        SQLite::Statement q(m_db,
            "SELECT r.name "
            "FROM rooms r "
            "JOIN user_rooms ur ON ur.room_id = r.id "
            "JOIN users u       ON u.id = ur.user_id "
            "WHERE u.username = ? "
            "ORDER BY r.name");
        q.bind(1, user);                          // bind first (1-based)

        while (q.executeStep())                   // one iteration per room
            rooms.push_back(q.getColumn(0).getString());
    } catch (const SQLite::Exception& e) {
        std::cerr << "roombuild failed: " << e.what() << '\n';
    }
    return rooms;
}
bool Authentication::addRoom(const std::string& user, const std::string& room)
{
    try {
        SQLite::Transaction transaction(m_db);
        SQLite::Statement insertRoom(m_db,
            "INSERT OR IGNORE INTO rooms (name) VALUES (?)");
        insertRoom.bind(1, room);
        insertRoom.exec();

        SQLite::Statement grant(m_db,
            "INSERT OR IGNORE INTO user_rooms (user_id, room_id) "
            "SELECT u.id, r.id FROM users u, rooms r "
            "WHERE u.username = ? AND r.name = ?");
        grant.bind(1, user);
        grant.bind(2, room);
        const int granted = grant.exec();   // rows inserted

        if (granted == 0 && !userExists(user))
            return false;
        transaction.commit();
        return true;
    } catch (const SQLite::Exception& e) {
        std::cerr << "addroom failed: " << e.what() << '\n';
    }
    return false;
}


