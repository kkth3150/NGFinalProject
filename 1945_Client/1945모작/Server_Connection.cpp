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
        case S_PLAYER_CHOICE: {
            SendHeaderPacket headerPacket = { sizeof(S_PlayerChoicePacket),S_PLAYER_CHOICE };
            int retval = send(sock, reinterpret_cast<char*>(&headerPacket), sizeof(headerPacket), 0);

            S_InitDataPacket packet;
            packet.Connected = *(reinterpret_cast<bool*>(Temp.data));
            retval = send(sock, reinterpret_cast<char*>(&packet), sizeof(packet), 0);
        }
            break;
        case S_START: {
            SendHeaderPacket headerPacket = { sizeof(S_GamePlayStartPacket),S_START };
            int retval = send(sock, reinterpret_cast<char*>(&headerPacket), sizeof(headerPacket), 0);
            S_GamePlayStartPacket packet;
            packet.Connected = *(reinterpret_cast<bool*>(Temp.data));
            retval = send(sock, reinterpret_cast<char*>(&packet), sizeof(packet), 0);
        }
            break;
        case S_MY_PLAYER_MOVE: {
            SendHeaderPacket headerPacket = { sizeof(S_MyPlayer_MovePacket),S_MY_PLAYER_MOVE };
            int retval = send(sock, reinterpret_cast<char*>(&headerPacket), sizeof(headerPacket), 0);
            S_MyPlayer_MovePacket packet;
            memcpy(&packet, Temp.data, sizeof(S_MyPlayer_MovePacket));
            retval = send(sock, reinterpret_cast<char*>(&packet), sizeof(packet), 0);
        }
            break;

        default:
            break;
        }
    }
}

void CServer_Connection::ReceiveThread()
{
    while (!m_bTerminateThreads) {

        char buffer[512];
        int retval = recv(sock, buffer, sizeof(RecvHeaderPacket), 0);
        
        RecvHeaderPacket headerPacket;
        memcpy(&headerPacket, buffer, sizeof(headerPacket));

        if (headerPacket.length > 0) {
            retval = recv(sock, buffer, headerPacket.length, 0);
            if (retval == SOCKET_ERROR || retval == 0) {
                break;
            }
        }
        
        RecvQueue_data queueData;
        queueData.event = headerPacket.event;

        size_t dataLength = headerPacket.length;
        if (dataLength > sizeof(queueData.data)) {
            dataLength = sizeof(queueData.data);
        }
      /*  memcpy(queueData.data, buffer, dataLength);
        if (queueData.event == R_PLAYER_MOVE) {

            R_PlayerMovePacket Temp;
            memcpy(&Temp, queueData.data, 16);
            int a = Temp.P1X;
            int B = Temp.P1Y;
        }*/
        std::lock_guard<std::mutex> lock(receiveMutex);
        receiveQueue.push(queueData);
    }
}

//void CServer_Connection::ReceiveThread()
//{
//    while (!m_bTerminateThreads) {
//
//        // Step 1: 헤더 패킷 수신
//        RecvHeaderPacket headerPacket;
//        int receivedBytes = 0;
//
//        while (receivedBytes < sizeof(headerPacket)) {
//            int retval = recv(sock, reinterpret_cast<char*>(&headerPacket) + receivedBytes, sizeof(headerPacket) - receivedBytes, 0);
//            if (retval == SOCKET_ERROR || retval == 0) {
//                // 에러 또는 연결 종료
//                return;
//            }
//            receivedBytes += retval;
//        }
//
//        // Step 2: 데이터 패킷 수신
//        size_t dataLength = headerPacket.length;
//        if (dataLength > sizeof(RecvQueue_data::data)) {
//            dataLength = sizeof(RecvQueue_data::data); // 최대 수신 가능 크기로 제한
//        }
//
//        char buffer[sizeof(RecvQueue_data::data)];
//        receivedBytes = 0;
//
//        while (receivedBytes < dataLength) {
//            int retval = recv(sock, buffer + receivedBytes, dataLength - receivedBytes, 0);
//            if (retval == SOCKET_ERROR || retval == 0) {
//                // 에러 또는 연결 종료
//                return;
//            }
//            receivedBytes += retval;
//        }
//
//        // Step 3: 수신된 데이터를 큐에 추가
//        RecvQueue_data queueData;
//        
//        queueData.event = headerPacket.event; 
//        memcpy(queueData.data, buffer, dataLength);
//
//        if (queueData.event == R_PLAYER_MOVE) {
//            
//            R_PlayerMovePacket Temp;
//            memcpy(&Temp, queueData.data, 16);
//            int a = Temp.P1X;
//            int B = Temp.P1Y;
//        }
//
//        // Lock을 사용하여 큐에 안전하게 push
//        {
//            std::lock_guard<std::mutex> lock(receiveMutex);
//            receiveQueue.push(queueData);
//        }
//    }
//}
void CServer_Connection::Push_SendQueue(SendQueue_data Data)
{
    std::lock_guard<std::mutex> lock(sendMutex);
    sendQueue.emplace(Data);
    sendCv.notify_one();
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

void CServer_Connection::Lock_RecvQueue()
{
    receiveMutex.lock();
}

void CServer_Connection::Unlock_RecvQueue()
{
    receiveMutex.unlock();
}

bool CServer_Connection::Get_RecvQueueData(RecvQueue_data& data)
{
    if (receiveQueue.empty()) {
        return false;
    }

    data = receiveQueue.front();
    receiveQueue.pop();
    return true;
}
