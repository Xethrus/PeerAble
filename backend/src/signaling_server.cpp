#include "signaling_server.h"

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

void signaling_server::on_message(websocketpp::connection_hdl handle, message_ptr message) {
  if(message_handler_) {
    message_handler_(message);
  }
}
