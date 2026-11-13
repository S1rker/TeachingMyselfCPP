#include "migrate.h"
#include <SQLiteCpp/SQLiteCpp.h>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace fs = std::filesystem;

void migrate(SQLite::Database& db, const fs::path& migrationsDir) {
    if (!fs::is_directory(migrationsDir))
        throw std::runtime_error("Migrations folder not found: " + migrationsDir.string());

    std::vector<fs::path> files;
    for (const auto& entry : fs::directory_iterator(migrationsDir))
        if (entry.path().extension() == ".sql") files.push_back(entry.path());
    std::sort(files.begin(), files.end());

    const size_t current = static_cast<size_t>(db.execAndGet("PRAGMA user_version").getInt());

    for (size_t i = current; i < files.size(); ++i) {
        std::ifstream in(files[i]);
        if (!in) throw std::runtime_error("Cannot read " + files[i].string());
        std::stringstream sql;
        sql << in.rdbuf();

        SQLite::Transaction tx(db);   // rolls back automatically if exec throws
        db.exec(sql.str());
        db.exec("PRAGMA user_version = " + std::to_string(i + 1));
        tx.commit();
    }
}
