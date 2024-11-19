#include "Client_Session.h"
#include "Level_Manager.h"
#include <thread>
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;


const int targetFPS = 30;
const int frameDelay = 1000 / targetFPS;

SOCKET g_listenSocket;
SOCKET g_clientSockets[CLIENT_END];
ClientSession* g_clientSessions[CLIENT_END];


int main() {
    LARGE_INTEGER frequency;
    LARGE_INTEGER frameStart, frameEnd;
    QueryPerformanceFrequency(&frequency);
    int frameCount = 0;
    DWORD fpsTimer = GetTickCount64();

    int retval;
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        return 1;
    printf("[알림] 윈속 초기화 성공\n");

    SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    //if (listen_sock == INVALID_SOCKET)
    //    err_quit("socket()");

    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(SERVERPORT);
    retval = bind(listen_sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    //if (retval == SOCKET_ERROR)
    //    err_quit("bind()");

    retval = listen(listen_sock, SOMAXCONN);
    //if (retval == SOCKET_ERROR)
    //    err_quit("listen()");



    CLevel_Manager::Get_Instance()->Level_Change(LEVEL_MENU);


    while (true) {
        SOCKET clientSocket = accept(listen_sock, NULL, NULL);
        if (clientSocket == INVALID_SOCKET) {
            continue;
        }

        u_long on = 1;
        ioctlsocket(clientSocket, FIONBIO, &on);

        // 새로운 ClientSession 객체 생성 및 시작
        for (int i = 0; i < CLIENT_END; ++i) {
            if (g_clientSessions[i] == nullptr) {
                g_clientSessions[i] = new ClientSession(clientSocket, i);
                g_clientSessions[i]->Start();
                std::cout << "클라이언트 " << i << " 연결됨\n";
                break;
            }
        }
    }

    // 서버 종료 시 리소스 해제
    closesocket(listen_sock);
    CLevel_Manager::Get_Instance()->Release();
    WSACleanup();

    return 0;
}

