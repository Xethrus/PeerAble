#include "user_management.h"
#include <stdexcept>
void UserManager::add_user(const std::string& name, websocketpp::connection_hdl handle) {
  if(!user_exists(name)) {
    users_.insert({name, User(name,handle)});
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

websocketpp::connection_hdl User::get_handle() const {
  return connection_handle_;
}

websocketpp::connection_hdl UserManager::get_connection_handle(const std::string& name) const {
    auto it = users_.find(name);
    if(it != users_.end()) {
      return it->second.get_handle();
    }
    return websocketpp::connection_hdl();
}
