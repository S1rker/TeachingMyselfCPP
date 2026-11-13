#pragma once

#include <memory>
#include <string>
#include <vector>
#include <SQLiteCpp/SQLiteCpp.h>

namespace PasswordHasher {
    // Returns "iterations$salt_base64$hash_base64"
    std::string hash(const std::string& password);

    // Checks a password against a string produced by hash()
    bool verify(const std::string& password, const std::string& stored);
}


class Authentication {
public:
    Authentication();
    ~Authentication();   // must be defined in the .cpp when using unique_ptr with a forward-declared type
    bool loginCheck(const std::string& user, const std::string& password);
    bool regCheck(const std::string& user, const std::string& password);

    std::vector<std::string> roomBuild(const std::string& user);

    bool addRoom(const std::string& user, const std::string& room);
    
    SQLite::Database m_db;

private:
    bool login(const std::string& user, const std::string& password);
    bool registration(const std::string&, const std::string&);
    bool userExists(const std::string& user);
    
};