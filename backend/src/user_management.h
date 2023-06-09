#pragma once

#include <optional>
#include <string>
#include <unordered_set>
#include <unordered_map>

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <websocketpp/common/connection_hdl.hpp>

enum class DocumentState {
  AVAILABLE,
  UNAVAILABLE,
};

class User {

public:
  explicit User(const std::string& name, websocketpp::connection_hdl handle) : name_(name), connection_handle_(handle) {}

  void set_name(const std::string& name) {
    name_ = name;
  }
  const std::string& get_name() {
    return name_;
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
  //websocketpp::connection_hdl get_connection_handle(const std::string& name) const;
  const std::optional<std::string> get_user(websocketpp::connection_hdl handle);

//  struct connection_hdl_hash {
//    std::size_t operator()(const websocketpp::connection_hdl& handle) const {
//      return std::hash<void*>()(handle.lock().get());
//    }
//  };

private:
 //users_ //name -> user
 //inverse_users_ //handle -> name
  std::unordered_map<std::string, User> users_;
  //std::unordered_map<websocketpp::connection_hdl, std::string, connection_hdl_hash> inverse_users_;
};

