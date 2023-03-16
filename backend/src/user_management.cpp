#include "user_management.h"
#include <stdexcept>
void UserManager::add_user(const std::string& name) {
  if(!user_exists(name)) {
    users_.insert(name);
  } else {
    throw std::invalid_argument("user exists");
  }
}

void UserManager::remove_user(const std::string& name) {
  if(user_exists(name)) {
    users_.erase(name);
  } else {
    throw std::invalid_argument("user does not exist");
  }
}

bool UserManager::user_exists(const std::string& name) const {
    return users_.count(name) > 0;
}

