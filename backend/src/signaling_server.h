#pragma once

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include "user_management.h"
#include <set>


class SignalingServer {
public:
  SignalingServer(UserManager& user_manager) : user_manager_(user_manager) {}
  typedef websocketpp::server<websocketpp::config::asio> server;
  typedef server::message_ptr message_ptr;
  typedef std::function<void(message_ptr)> message_handler;
  
  void start(uint16_t port);
  void stop();
  void set_message_handler(message_handler handler);

  void handle_join_message(message_ptr msg);
  void handle_leave_message(message_ptr msg);

  std::string get_message_type(const message_ptr& msg);


private:
  server server_;
  message_handler message_handler_;
  UserManager& user_manager_;
  std::set<websocketpp::connection_hdl, std::owner_less<websocketpp::connection_hdl>> connections_;
  
  
  void on_open(websocketpp::connection_hdl hdl);
  void on_close(websocketpp::connection_hdl hdl);
  void on_message(websocketpp::connection_hdl hd1, message_ptr msg);
  void broadcast_message(message_ptr msg);

};

