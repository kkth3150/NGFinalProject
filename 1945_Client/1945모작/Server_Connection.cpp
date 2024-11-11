#include "pch.h"
#include "Server_Connection.h"
#include "ErrorMsg.h"

#define SERVERPORT 9000

CServer_Connection* CServer_Connection::m_pInstance = nullptr;

CServer_Connection::CServer_Connection()
{
}

CServer_Connection::~CServer_Connection()
{
}

void CServer_Connection::Initialize(const char* ServerIP)
{

    int retval;
    u_long mode = 1;
    WSADATA wsa;
    
    ioctlsocket(sock, FIONBIO, &mode);

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        return;
    printf("[알림] 윈속 초기화 성공\n");



    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET)
        err_quit("socket()");

    ioctlsocket(sock, FIONBIO, &mode);

    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    inet_pton(AF_INET, ServerIP, &serveraddr.sin_addr);
    serveraddr.sin_port = htons(SERVERPORT);

    retval = connect(sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));

    if (retval == SOCKET_ERROR)
        err_quit("connect()");
}

void CServer_Connection::Send_Data(SEND_EVENT_TYPE eEvent, void* Data)
{
    switch (eEvent) {
    case S_PLAYER_CHOICE: {

        S_PlayerChoicePacket* eventData = static_cast<S_PlayerChoicePacket*>(Data);

        SendHeaderPacket header;
        header.length = sizeof(S_PlayerChoicePacket);
        header.event = S_PLAYER_CHOICE;

        int retval = send(sock, reinterpret_cast<const char*>(&header), sizeof(SendHeaderPacket), 0);
        if (retval == SOCKET_ERROR)
            err_quit("send() - header");

        retval = send(sock, reinterpret_cast<const char*>(eventData), sizeof(S_PlayerChoicePacket), 0);
        if (retval == SOCKET_ERROR)
            err_quit("send() - PlayerChoicePacket");
    }
        break;

    case S_KEY_INPUT:
    {

        S_KeyInputPacket* eventData = static_cast<S_KeyInputPacket*>(Data);

        SendHeaderPacket header;
        header.length = sizeof(S_KeyInputPacket);
        header.event = S_PLAYER_CHOICE;

        int retval = send(sock, reinterpret_cast<const char*>(&header), sizeof(SendHeaderPacket), 0);
        if (retval == SOCKET_ERROR)
            err_quit("send() - header");

        retval = send(sock, reinterpret_cast<const char*>(eventData), sizeof(S_KeyInputPacket), 0);
        if (retval == SOCKET_ERROR)
            err_quit("send() - KeyInputPacket");
    }
        break;

    default:
        break;
    }

}

ReceiveDataResult CServer_Connection::Receive_Data()
{
    RecvHeaderPacket header;
    int retval = recv(sock, reinterpret_cast<char*>(&header), sizeof(RecvHeaderPacket), 0);
    if (retval == SOCKET_ERROR || retval == 0) {
        err_quit("recv() failed or connection closed");
    }

    switch (header.event) {
    case R_PLAYER_CHOICE: {
        auto* eventData = new R_PlayerChoicePacket;
        retval = recv(sock, reinterpret_cast<char*>(eventData), sizeof(R_PlayerChoicePacket), 0);
        if (retval == SOCKET_ERROR || retval == 0) {
            err_quit("recv() failed - R_PlayerChoicePacket");
        }
        return { R_PLAYER_CHOICE, eventData };
    }
        break;

    case R_LEVEL_CHANGE:
    {
        auto* eventData = new R_LevelChangePacket;
        retval = recv(sock, reinterpret_cast<char*>(eventData), sizeof(R_LevelChangePacket), 0);
        if (retval == SOCKET_ERROR || retval == 0) {
            err_quit("recv() failed - R_LevelChangePacket");
        }
        return { R_LEVEL_CHANGE, eventData };
    }

    case R_EVENT_END:
        break;
    }

}


void CServer_Connection::Release()
{
}