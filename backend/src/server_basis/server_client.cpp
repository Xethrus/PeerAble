#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include <iostream>

typedef websocketpp::client<websocketpp::config::asio_client> client;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

typedef websocketpp::config::asio_client::message_type::ptr message_ptr;

//handlers

void on_open(client* server_client, websocketpp::conneection_hdl handle) {
  std::string message = "message sent";
  server_client->send(handle,message,websocketpp::frame::opcode::text);
  server_client->get_alog().write(websocketpp::log::alevel::app, "sent message: "+message);
}

