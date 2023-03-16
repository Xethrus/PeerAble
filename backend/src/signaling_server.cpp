#include "signaling_server.h"
#include "user_management.h"
#include <nlohman/json>

SignalingServer::SignalingServer(UserManager& userManager) : userManager_(userManager) {
  server_.init_asio();

  server_.set_open_handler(bind(&SignalingServer::on_open, this, ::_1));
  server_.set_close_handler(bind(&SignalingServer::on_close, this, ::_1));
  server_.set_message_handler(bind(&SignalingServer::on_message, this, ::_1, ::_2));
}

void SignalingServer::run(uint16_t port) {
    // Start the WebSocket server
  server_.listen(port);
  server_.start_accept();
  server_.run();
}

void SignalingServer::on_open(websocketpp::connection_hdl handle) {
  //store connection for later
  connections_.insert(handle);
}

void SignalingServer::on_message(websocketpp::connection_hdl handle, server::message_ptr message) {
  //converting to string from client message
  std::string message_string = message->get_payload();
  //parsing
  auto json_parsed = nlohmann::json::parse(message_string)

  
  //check message type and name
  if(json_parsed["type"] == "join" && json_parsed.contains("name")) {
    //store name and connection in users_ map
    std::string client_name = json_parsed["name"];
    userManager_.add_user(client_name, handle);

    //send welcome to client
    nlohmann::json welcome_message;
    welcome_message["type"] = "welcome";
    welcome_message["message"] = "Welcome, " + client_name;
    server_.send(handle, welcome_message.dump(), websocketpp::frame::opcode::text);
  }
}

void SignalingServer::on_close(websocketpp::connection_hdl handle) {
  //retrieve client name with handle
  std::string client_name = clients_[handle];

  //clear client from users_ map
  userManager_.remove_user(client_name);
  //remove handle fro connections_
  connections_.erase(handle);

  //send leave message
  //
  nlohmann::json leave_message;
  leave_message["type"] = "leave";
  leave_message["message"] = client_name + " has left";
  std::string leave_message_string = leave_message.dump();

  for (auto connection : connections_) {
    server_.send(connection, leave_message_string, websocketpp::frame::opcode::text);
  }
}
