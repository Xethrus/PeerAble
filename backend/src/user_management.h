#pragma once

#include <string>
#include <unordered_set>

class User {
public:
  explicit User(const std::string& name, websocketpp::connection_hdl handle) : name_(name), connection_handle_(handle) {}
}
  void set_name(const std::string& name) {
    name_ = name;
  }
  websocketpp::connection_hdl get_handle() const;

private:
  std::string name_;
  DocumentState document_state_;
  websocketpp::connection_hdl connection_handle_;
};


class UserManager {
public:
  void add_user(const std::string& name, websocketpp::connection_hdl handle);
  //maybe make remove user also take handle
  void remove_user(const std::string& name);
  bool user_exists(const std::string& name) const;
  websocketpp::connection_hdl get_connection_handle(const std::string& name) const;

private:
  std::unordered_map<std::string, User> users_;
};

