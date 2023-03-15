#include "signaling_server.h"
#include "user_management.h"
#include "message_format.h"

#include <nlohmann/json.hpp>

void signaling_server::start(uint16_t port) {
  server_.init_asio();

  server_.set_message_handler(std::bind(&signaling_server::on_message, this, std::placeholders::_1, std::placeholders::_2));

  server_.listen(port);
  server_.start_accept();

  server_.run();
}

void signaling_server::stop() {
  server_.stop();
}

void signaling_server::set_message_handler(message_handler handler) {
  message_handler_ = handler;
}

void signaling_server::handle_join_message(message_ptr msg) {
  JoinMessage join_message = JoinMessage::deserialize(msg->get_payload());
  std::string username = join_message.username;

  try {
    user_manager_.add_user(username);
  } catch (std::exception& exception) {
    //handle errors
  }
  broadcast_message(msg);
}

void signaling_server::handle_leave_message(message_ptr msg) {
  LeaveMessage leave_message = LeaveMessage::deserialize(msg->get_payload());
  std::string username = leave_message.username;
  try {
    user_manager_.remove_user(username);
  } catch (std::exception& exception) {
    //handle errors
  }
  broadcast_message(msg);
}

void signaling_server::on_message(websocketpp::connection_hdl handle, message_ptr message) {
  std::string message_type = get_message_type(msg);


  if (message_type == k_join_message_type) {
    handle_join_message(msg);
  } else if (message_type == k_leave_message_type) {
    handle_leave_message(msg);
  }
//
//  if(message_handler_) {
//    message_handler_(message);
//  }
  
}
