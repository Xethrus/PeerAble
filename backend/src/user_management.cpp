#include "user_management.h"
#include <stdexcept>

void UserManager::add_user(const std::string& name, websocketpp::connection_hdl handle) {
  if(!user_exists(name)) {
    users_.insert({name, User(name,handle)});
    inverse_users_.insert({handle, name});
  } else {
    throw std::invalid_argument("user exists");
  }
}

void UserManager::remove_user(const std::string& name) {
  if(user_exists(name)) {
    inverse_users_.erase(users_.at(name).connection_handle_);
    users_.erase(name);
  } else {
    throw std::invalid_argument("user does not exist");
  }
}

bool UserManager::user_exists(const std::string& name) const {
    if(users_.count(name) > 0 && inverse_users_.count(name) >0) {
    return true;
  } else {
    return false;
  }
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
