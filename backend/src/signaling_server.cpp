#include "signaling_server.h"
#include "user_management.h"
#include "message_format.h"

#include <nlohmann/json.hpp>

void SignalingServer::start(uint16_t port) {
  server_.init_asio();
  server_.set_open_handler(std::bind(&SignalingServer::on_open, this, std::placeholders::_1));
  server_.set_close_handler(std::bind(&SignalingServer::on_close, this, std::placeholders::_1));
  server_.set_message_handler(std::bind(&SignalingServer::on_message, this, std::placeholders::_1, std::placeholders::_2));

  server_.listen(port);
  server_.start_accept();

  server_.run();
}

void SignalingServer::stop() {
  server_.stop();
}

void SignalingServer::set_message_handler(message_handler handler) {
  message_handler_ = handler;
}

void SignalingServer::on_open(websocketpp::connection_hdl hdl) {
  connections_.insert(hdl);
}

void SignalingServer::on_close(websocketpp::connection_hdl hdl) {
  connections_.erase(hdl);
}

void SignalingServer::handle_join_message(message_ptr msg) {
  JoinMessage join_message = JoinMessage::deserialize(msg->get_payload());
  std::string username = join_message.username;

  user_manager_.add_user(username);
  broadcast_message(msg);
}

void SignalingServer::handle_leave_message(message_ptr msg) {
  LeaveMessage leave_message = LeaveMessage::deserialize(msg->get_payload());
  std::string username = leave_message.username;

  user_manager_.remove_user(username);
  broadcast_message(msg);
}

std::string SignalingServer::get_message_type(const message_ptr& message) {
  try {
nlohmann::json json_message = nlohmann::json::parse(message->get_payload());
    return json_message["type"];
  } catch(const std::exception&) {
    throw std::runtime_error("Invalid message format");
  }
}

void SignalingServer::on_message(websocketpp::connection_hdl handle, message_ptr message) {
  std::string message_type = get_message_type(message);
  if (message_type == k_join_message_type) {
    handle_join_message(message);
  } else if (message_type == k_leave_message_type) {
    handle_leave_message(message);
  }
}

void SignalingServer::broadcast_message(message_ptr msg) {
  for (auto connection : connections_) {
    server_.send(connection, msg);
  }
}
