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
    WSADATA wsa;
    
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        return;

    printf("[알림] 윈속 초기화 성공\n");

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET)
        err_quit("socket()");

    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    inet_pton(AF_INET, ServerIP, &serveraddr.sin_addr);
    serveraddr.sin_port = htons(SERVERPORT);

    retval = connect(sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));

    if (retval == SOCKET_ERROR)
        err_quit("connect()");

    senderThread    = std::thread(&CServer_Connection::SendThread, this);
    receiverThread  = std::thread(&CServer_Connection::ReceiveThread, this);
}

void CServer_Connection::SendThread()
{
    while (!m_bTerminateThreads) {
        std::unique_lock<std::mutex> lock(sendMutex);
        sendCv.wait(lock, [this]() { return !sendQueue.empty() || m_bTerminateThreads; });

        if (m_bTerminateThreads) break;

        SendQueue_data Temp = sendQueue.front();
        sendQueue.pop();
        lock.unlock();

        SEND_EVENT_TYPE eventType = Temp.event;

        switch (eventType) {
        case S_INIT_DATA: {
            SendHeaderPacket headerPacket = { sizeof(S_InitDataPacket),S_INIT_DATA };
            int retval = send(sock, reinterpret_cast<char*>(&headerPacket), sizeof(headerPacket), 0);

            S_InitDataPacket packet;
            packet.Connected = *(reinterpret_cast<bool*>(Temp.data));
            retval = send(sock, reinterpret_cast<char*>(&packet), sizeof(packet), 0);
        }
            break;
        case S_PLAYER_CHOICE:
            break;
        case S_KEY_INPUT:
            break;


        default:
            break;
        }
    }
}

void CServer_Connection::ReceiveThread()
{
    while (!m_bTerminateThreads) {
        ReceiveDataResult result = Receive_Data();

        std::lock_guard<std::mutex> lock(receiveMutex);
        // 수신된 데이터를 큐에 추가하여 후속 처리가 가능하게 함
       /* receiveQueue.push(result);*/
    }
}


void CServer_Connection::Push_SendQueue(SendQueue_data Data)
{
    std::lock_guard<std::mutex> lock(sendMutex);
    sendQueue.emplace(Data);
    sendCv.notify_one();
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
    case R_LEVEL_CHANGE: {
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

    return { R_EVENT_END, nullptr };
}

void CServer_Connection::Release()
{
    m_bTerminateThreads = true;
    sendCv.notify_all();

    if (senderThread.joinable())
        senderThread.join();
    if (receiverThread.joinable())
        receiverThread.join();

    closesocket(sock);
    WSACleanup();
}