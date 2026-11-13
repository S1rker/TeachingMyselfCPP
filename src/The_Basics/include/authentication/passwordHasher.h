#pragma once
#include <string>

namespace PasswordHasher {
    // Returns "iterations$salt_base64$hash_base64"
    std::string hash(const std::string& password);

    // Checks a password against a string produced by hash()
    bool verify(const std::string& password, const std::string& stored);
}