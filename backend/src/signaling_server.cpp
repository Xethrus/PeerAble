#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

typedef websocketpp::server<websocketpp::config::asio> server;

class signaling_server {
public:
  typedef server::message_ptr message_ptr;
  typedef std::function<void(message_ptr)> message_handler;

  void start(uint16_t port) {
    //init the server's Asio I/0 service
    server_.init_asio();

    //setup server- sets message handler to be the 'on_message' function of the current 'signaling_server'
    //bind binds the on_message member function to the placeholders for the connection handleand message arguments
    server_.set_message_handler(std::bind(&signaling_server::on_message, this, std::placeholders::_1, std::placeholders::_2));

    //start server up
    server_.listen(port);
    server_.start_accept();
    
    //start the asio io_service loop
    server_.run();
  }

  void stop() {
    server_.stop();
  }

  void set_message_handler(message_handler handler) {
    message_handler_ = handler;
  }

private:
  server server_;
  message_handler message_handler_;

  void on_message(websocketpp::connection_hd1 hd1, message_ptr msg) {
    if(message_handler_) {
      message_handler_(msg);
    }
  }

};
