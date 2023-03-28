#include "mongoose.h"
#include <iostream>

static const char *s_url = "ws://107.131.124.5:8000/websocket";

static void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
  if (ev == MG_EV_OPEN) {
    c->is_hexdumping = 1;
  } else if (ev == MG_EV_ERROR) {
    //on error log error message
    MG_ERROR(("%p %s", c->fd, (char *) ev_data));
  } else if (ev == MG_EV_WS_OPEN) {
    //when websocket handshake is successful, send message
    mg_ws_send(c, "hello", 5, WEBSOCKET_OP_TEXT);
  } else if (ev == MG_EV_WS_MSG) {
    //when we get echo response, print it
    struct mg_ws_message *wm = (struct mg_ws_message *) ev_data;
    std::cout << "got echo reply: " << (int) wm->data.len << " " << wm->data.ptr;
  }

  if(ev == MG_EV_ERROR || ev == MG_EV_CLOSE || ev == MG_EV_WS_MSG) {
    *(bool *) fn_data = true; //signal that we're done
  }
}

int main(void) {
  struct mg_mgr mgr; // event manager
  bool done = false; // event handler flips it to true
  struct mg_connection *c; // client connection
  mg_mgr_init(&mgr); // initialise event manager
  mg_log_set(MG_LL_DEBUG); // set log level
  c = mg_ws_connect(&mgr, s_url, fn, &done, NULL); // create client
  while(c && done == false) mg_mgr_poll(&mgr, 1000); // wait for echo
  mg_mgr_free(&mgr); //deallocate resources
  return 0;
}
