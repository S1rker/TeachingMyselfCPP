#pragma once
#include <filesystem>

namespace SQLite { class Database; }

void migrate(SQLite::Database& db, const std::filesystem::path& migrationsDir);