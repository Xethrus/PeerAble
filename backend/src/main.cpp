#include "signaling_server.h"
#include "user_management.h"

int main() {
    UserManager userManager;
    SignalingServer signalingServer(userManager);

    signalingServer.run(8000); 

    return 0;
}

