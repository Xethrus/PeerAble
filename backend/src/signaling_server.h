#pragma once

#include "user_management.h"
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <websocketpp/common/connection_hdl.hpp>
#include <unordered_map>
#include <unordered_set>

class SignalingServer {
public:
    typedef websocketpp::server<websocketpp::config::asio> server;
    explicit SignalingServer(UserManager& userManager);
    void run(uint16_t port);

private:
    
    std::unordered_map<websocketpp::connection_hdl, std::string, std::owner_less<websocketpp::connection_hdl>> clients_;
    UserManager userManager_;
    websocketpp::server<websocketpp::config::asio> server_;
    
    //my connections set for storing client connections
//    std::unordered_set<websocketpp::connection_hdl, std::owner_less<websocketpp::connection_hdl>> connections_;
  //
    void on_message(websocketpp::connection_hdl handle, server::message_ptr message);
    void on_open(websocketpp::connection_hdl handle);
    void on_close(websocketpp::connection_hdl handle);
};
