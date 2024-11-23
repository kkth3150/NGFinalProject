#include "pch.h"
#include "Client_Connection.h"
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


int main() {
    LARGE_INTEGER frequency;
    LARGE_INTEGER frameStart, frameEnd;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&frameStart);
    int frameCount = 0;
    DWORD fpsTimer = GetTickCount64();

    int retval;
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        return 1;
    printf("[알림] 윈속 초기화 성공\n");

    SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(SERVERPORT);
    retval = bind(listen_sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));


    retval = listen(listen_sock, SOMAXCONN);

    CLevel_Manager::Get_Instance()->Level_Change(LEVEL_MENU);


    CClient_Connection* clients[CLIENT_END];
    for (int i = 0; i < CLIENT_END; ++i) {
        SOCKET clientSock = accept(listen_sock, NULL, NULL);
        if (clientSock == INVALID_SOCKET) {
            cerr << "Client connection failed" << endl;
            continue;
        }
        cout << "Client " << i + 1 << " connected" << endl;

        clients[i] = CClient_Connection::Get_Instance(static_cast<CLIENT_ID>(i));
        clients[i]->Set_SOCKET(clientSock);  // 수락된 소켓을 설정
        clients[i]->Initialize();           // 초기화
    }



    while (true) {


        CLevel_Manager::Get_Instance()->Update();       // 각 클라이언트의 데이터 처리
        CLevel_Manager::Get_Instance()->Late_Update();  // 추가적인 업데이트 처리

        // 원하는 프레임 대기
        QueryPerformanceCounter(&frameEnd);
        DWORD frameTime = (frameEnd.QuadPart - frameStart.QuadPart) * 1000 / frequency.QuadPart;
        if (frameDelay > frameTime) {
            Sleep(frameDelay - frameTime);
        }
        frameStart = frameEnd;
    }

    // 서버 종료 시 리소스 해제
    for (int i = 0; i < CLIENT_END; ++i) {
        clients[i]->Release();  // 각 클라이언트 연결 해제
    }
    CClient_Connection::Destroy_Instance();
    closesocket(listen_sock);
    WSACleanup();

    return 0;
}

