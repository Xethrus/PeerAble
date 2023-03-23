//websocketpp
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <nlohmann/json.hpp>
//boost.beast
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/filesystem.hpp>


#include <thread>
#include <fstream>
#include <iostream>
#include <map>
#include <mutex>
#include <set>
#include <vector>

typedef websocketpp::server<websocketpp::config::asio> server;

std::mutex connections_mutex;
std::map<int, websocketpp::connection_hdl>, std::owner_less<websocketpp::connection_hdl>> connections;

class routing_server {
public:
  std::vector<std::string> user_messages;

  int generate_user_id() {
    static int user_id = 1;
    return user_id++;
  }
  void on_open(websocketpp::connection_hdl handle) {
    std::lock_guard<std::mutex> lock(connections_mutex);
    int user_id = generate_user_id();
    connections[user_id] = handle;
    std::cout << "User " << user_id << " connected" << std::endl;
  }
  void on_close(websocketpp::connection_hdl handle) {
    std::lock_guard<std::mutex> lock(connections_mutex);
    for (auto it = connections.begin(); it != connections.end(); ++it) {
      if (it->second.lock() == handle.lock()) {
        std::cout << "User " << it->first << " disconnected" << std::endl;
        connections.erase(it);
        break;
      }
    }
  }
  void on_message(server* server, websocketpp::connection_hdl handle, server::message_ptr message) {
    std::lock_guard<std::mutex> lock(connections_mutex);
    //adding message to the list of messages
    user_messages.push_back(message->get_payload());
    
    //serialize the list of messages as a json string
    nlohmann::json json_messages(user_messages);
    std::string serialized_messages = json_messages.dump();

    //broadcast the updated list of messages
    for (auto const& connection : connections) {
      auto connection_hdl = connection.second;
      if(connection_hdl.lock() != handle.lock()) {
        //server->send(connection_hdl, message->get_payload(), message->get_opcode());
        server->send(connection_hdl, serialized_messages, message->get_opcode());
      }
    }
  }
};



//making alias 
using tcp = boost::asio::ip::tcp;
//adding namespace for easy ref
namespace http = boost::beast::http;

//takes tcp socket and a path string- we need to defined aserve file function because the http server needs to send static frontend files to clients
void serve_file(tcp::socket &socket, const std::string &path) {
  //Open the file to be served to the clients and determine its size, so that we can set the content-length header in the http response
    http::file_body::value_type file;
    file.open(path.c_str(), boost::beast::file_mode::read);
    auto const size = file.size();
//creates the ok reponse object for success use
    http::response<http::file_body> res{
        http::status::ok, 11};
    //these set the server and content-type headers, they also assign the file object to the response body to send the file's contents to the client
    res.set(http::field::server, "WebSocket++ Server");
    res.set(http::field::content_type, "text/html");
    res.content_length(size);
    res.body() = std::move(file);
    //this writes the response to the tcp socket passed in above
    http::write(socket, res);
}

void start_http_server() {
  //create I/0 context and tcp acceptor that listens on port 8080 with ipv4. Context and acceptor are needed to manage and accept incoming client connections
  boost::asio::io_context ioc{1};
  tcp::acceptor acceptor{ioc, {tcp::v4(), 80}};
//this is an infinite loop so we can keep accepting incoming connections
  for (;;) {
    //new tcp socket using the i/o context
    tcp::socket socket{ioc};
    acceptor.accept(socket);

    boost::beast:flat_buffer buffer;
    http::request<http::string_body> request;
    http::read<socket, buffer, request);

    if (req.target() == "/") {
        serve_file(socket, "frontend/index.html");
    } 
  }
}

void start_websocket_server() {
  routing_server route_srv;
  server ws_server;

  //init asio transport
  ws_server.init_asio();
  
  //setup handlers
  ws_server.set_open_handler(bind(&routing_server::on_open, &route_srv, ::_1));
  ws_server.set_close_handler(bind(&routing_server::on_close, &route_srv, ::_1));
  ws_server.set_message_handler(bind(&routing_server::on_message, &route_srv, ::_1, ::_2));

  //listen on port
  uint16_t port = 8000;
  ws_server.listen(port);

  //start server accept loop
  ws_server.start_accept();

  //start asio io_service run loop
  ws_server.run();
}


int main() {
  std::thread http_server_thread(start_http_server);
  std::thread websocket_server_thread(start_websocket_server);

  http_server_thread.join();
  websocket_server_thread.join();

  return 0;
}
