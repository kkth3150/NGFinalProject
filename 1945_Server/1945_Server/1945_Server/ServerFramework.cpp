#include "Common.h"
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
HANDLE g_hClientEvents[CLIENT_END];
thread g_clientThreads[CLIENT_END];


void ClientHandler(SOCKET clientSocket, int clientIndex);
void Handle_PlayerChoice(const S_PlayerChoicePacket& playerChoice, int clientIndex);
void Handle_KeyInput(const S_KeyInputPacket& keyInput, int clientIndex);

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
    if (listen_sock == INVALID_SOCKET)
        err_quit("socket()");

    u_long on = 1;
    retval = ioctlsocket(listen_sock, FIONBIO, &on);


    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = PF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(SERVERPORT);
    retval = bind(listen_sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    if (retval == SOCKET_ERROR)
        err_quit("bind()");

    retval = listen(listen_sock, SOMAXCONN);
    if (retval == SOCKET_ERROR)
        err_quit("listen()");



    CLevel_Manager::Get_Instance()->Level_Change(LEVEL_MENU);

    // 클라이언트 연결 대기 및 처리
    while (true) {
        SOCKET clientSocket = accept(listen_sock, NULL, NULL);
        if (clientSocket == INVALID_SOCKET) {
            continue;
        }
        else {
            printf("클라이언트 연결됨, 소켓: %d\n", clientSocket);
        }

        // 클라이언트 소켓을 g_clientSockets에 할당
        for (int i = 0; i < CLIENT_END; ++i) {
            printf("g_clientSockets[%d]: %d\n", i, g_clientSockets[i]);
            if (g_clientSockets[i] == INVALID_SOCKET) {
                g_clientSockets[i] = clientSocket;
                g_clientThreads[i] = std::thread(ClientHandler, clientSocket, i);
                g_clientThreads[i].detach();
                printf("클라이언트 %d 연결됨\n", i);
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

void ClientHandler(SOCKET clientSocket, int clientIndex) {
    char recvBuffer[1024];  // 데이터를 받을 버퍼
    int recvSize;

    // 데이터 수신 및 처리
    while (true) {
        recvSize = recv(clientSocket, recvBuffer, sizeof(recvBuffer), 0);
        if (recvSize == SOCKET_ERROR) {
            printf("클라이언트 %d 데이터 수신 오류\n", clientIndex);
            break;
        }
        else if (recvSize == 0) {
            printf("클라이언트 %d 연결 종료\n", clientIndex);
            break;
        }

        // 헤더 수신
        SendHeaderPacket header;
        memcpy(&header, recvBuffer, sizeof(SendHeaderPacket));

        // 헤더에 따라 데이터 타입 분기
        switch (header.event) {
        case S_PLAYER_CHOICE: {
            // 플레이어 선택 데이터 처리
            S_PlayerChoicePacket playerChoice;
            memcpy(&playerChoice, recvBuffer + sizeof(SendHeaderPacket), sizeof(S_PlayerChoicePacket));

            Handle_PlayerChoice(playerChoice, clientIndex);
        } break;

        case S_KEY_INPUT: {
            // 키 입력 데이터 처리
            S_KeyInputPacket keyInput;
            memcpy(&keyInput, recvBuffer + sizeof(SendHeaderPacket), sizeof(S_KeyInputPacket));

            // 키 입력 처리
            Handle_KeyInput(keyInput, clientIndex);
        } break;

        default:
            printf("알 수 없는 이벤트 타입: %d\n", header.event);
            break;
        }
    }

    // 클라이언트 소켓 종료
    closesocket(clientSocket);
    g_clientSockets[clientIndex] = INVALID_SOCKET;
    printf("클라이언트 %d 소켓 종료\n", clientIndex);
}

void Handle_PlayerChoice(const S_PlayerChoicePacket& playerChoice, int clientIndex) {

}

void Handle_KeyInput(const S_KeyInputPacket& keyInput, int clientIndex) {
}