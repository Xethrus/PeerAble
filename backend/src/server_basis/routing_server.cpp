#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include <iostream>
#include <map>
#include <mutex>
#include <set>

typedef websocketpp::server<websocketpp::config::asio> server;

std::mutex connections_mutex;
std::map<int, websocketpp::connection_hdl> connections;

class routing_server {
public:
  routing_server() {
    m_server
  }

  void on_open(websocketpp::connection_hdl handle) {
    std::lock_guard<std::mutex> lock(connections_mutex);
    static int user_id = 1;
    connections[user_id] = handle;
    user_id++;
  }
  void on_close(websocketpp::connection_hdl handle) {
    std::lock_guard<std::mutex> lock(connections_mutex);
    for (auto it = connections.begin(); it != connections.end(); ++it) {
      if (it->second.lock() == handle.lock()) {
        connections.erase(it);
        break;
      }
    }
  }
  void on_message(server* server, websocketpp::connection_hdl handle, server::message_ptr message) {
    std::lock_guard<std::mutex> lock(connections_mutex);
    for (auto const& connection : connections) {
      auto connection_hdl = connection.second;
      if(connection_hdl.lock() != handle.lock()) {
        server->send(connection_hdl, message->get_payload(), message->get_opcode());
      }
    }
  }
private:
  routing_server m_server;

};



int main() {

  return 0;
}
