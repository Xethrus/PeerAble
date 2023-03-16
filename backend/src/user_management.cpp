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

//
//
//

websocketpp::connection_hdl User::get_handle() const {
  return connection_handle_;
}

void UserManager::remove_user(const std::string& name) {
  if(user_exists(name)) {
    inverse_users_.erase(users_[name].get_handle());
    users_.erase(name);
  } else {
    throw std::invalid_argument("user does not exist");
  }
}

//
//
//

bool UserManager::user_exists(const std::string& name) const {
  return(users_.count(name) > 0);
}


//websocketpp::connection_hdl UserManager::get_connection_handle(const std::string& name) const {
//    auto it = users_[name];
//    if(it != users_.end()) {
//      return it->second.get_handle();
//    }
//    return websocketpp::connection_hdl();
//}

const std::string& UserManager::get_user(websocketpp::connection_hdl handle) {
  return inverse_users_[handle];
}

//custom hash
//struct connection_hdl_hash {
//std::size_t operator()(const websocketpp::connection_hdl& hdl) const {
//    return std::hash<std::shared_ptr<void>>()(hdl.lock());
//  }
//};
