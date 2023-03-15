#pragma once

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

typedef int butts

class signaling_server {
public:
  typedef websocketpp::server<websocketpp::config::asio> server;
  typedef server::message_ptr message_ptr;
  typedef std::function<void(message_ptr)> message_handler;

  void start(uint16_t port);
  void stop();
  void set_message_handler(message_handler handler);

private:
  server server_;
  message_handler message_handler_;
  
  void on_message(websocketpp::connection_hd1 hd1, message_ptr msg);

};

#endif /* SIGNALING_SERVER_H */
