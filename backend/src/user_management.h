#pragma once

#include <string>
#include <unordered_set>

class UserManager {
public:
    void add_user(const std::string& name);
    void remove_user(const std::string& name);
    bool user_exists(const std::string& name) const;

private:
    std::unordered_set<std::string> users_;
};

