#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include <iostream>

typedef websocketpp::client<websocketpp::config::asio_client> client;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

typedef websocketpp::config::asio_client::message_type::ptr message_ptr;

//handlers
//
//open close
void on_open(client* server_client, websocketpp::connection_hdl handle) {
  std::string message = "message sent";
  server_client->send(handle,message,websocketpp::frame::opcode::text);
  server_client->get_alog().write(websocketpp::log::alevel::app, "sent message: "+message);
}

void on_close(client* server_client, websocketpp::connection_hdl handle) {
  server_client->get_alog().write(websocketpp::log::alevel::app, "Connection closed");
}

//
//message
void on_message(client* server_client, websocketpp::connection_hdl handle, message_ptr message) {
  server_client->get_alog().write(websocketpp::log::alevel::app, "recieved message: "+message->get_payload());
  server_client->close(handle, websocketpp::close::status::normal,"");
}
//
//failure
void on_fail(client* server_client, websocketpp::connection_hdl handle) {
  server_client->get_alog().write(websocketpp::log::alevel::app, "Connection failed");
}

int main(int argc, char* argv[]) {
  client server_client;
  
  std::string uri = "107.131.124.5:8000";
  if (argc == 2) {
    uri = argv[1];
  }

  try {
    //setting logging policy if needed (config logging level)
    //comment out to reduce mem usage
    server_client.clear_access_channels(websocketpp::log::alevel::frame_header);
    server_client.clear_access_channels(websocketpp::log::alevel::frame_payload);
    //server_client.set_error_channels(websocketpp::log::elevel::none);

    //spin up asio
    server_client.init_asio();

    //register current handles
    server_client.set_open_handler(bind(&on_open,&server_client,::_1));
    server_client.set_close_handler(bind(&on_close,&server_client,::_1));
    server_client.set_message_handler(bind(&on_message,&server_client,::_1,::_2));
    server_client.set_close_handler(bind(&on_close,&server_client,::_1));

    //conncet to my uri
    //once even loop starts
    websocketpp::lib::error_code error_code;
  client::connection_ptr connection = server_client.get_connection(uri, error_code);
    server_client.connect(connection);
      //start the asio io_server run loop
    server_client.run();
  } catch (const std::exception & exception) {
    std::cout << exception.what() << std::endl;
  } catch (websocketpp::lib::error_code error_code) {
    std::cout << error_code.message() << std::endl;
  } catch (...) {
    std::cout << "error" << std::endl;
  }
}


