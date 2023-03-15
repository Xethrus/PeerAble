#include "user_management.h"
#include "signaling_server.h"

int main(int arc, char* arv[]) {
  //init user management class
  UserManager user_manager;
  
  //init signaling_server
  SignalingServer signaling_server;
  signaling_server.set_message_handler([&user_manager](const message_ptr& message) {
  //TODO: define stuff to HANDLE messages
});
  //start signaling server on port 8000
  signaling_server.start(8000);

  //run the io_service loop 
  signaling_server.run();


  return 0;
}
