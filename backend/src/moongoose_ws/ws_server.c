#include "mongoose.h"

static const char *s_listen_on = "ws://107.131.124.5:8000"
static const char *s_web_root = ".";

static void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
  if(ev == MG_EV_OPEN) {
    //means that that the connection is hexdumping
  } else if (ev == MG_EV_HTTP_MSG) {
    struct mg_http_message *hm = (struct mg_http_message *) ev_data;
    if(mg_http_match_uri(hm, "/websocket")) {
      mg_ws_upgrade(c, hm, NULL);
    } else if
  }
}
