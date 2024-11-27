#include "pch.h"
#include "Client_Connection.h"

CClient_Connection* CClient_Connection::m_pInstance[CLIENT_END] = {nullptr,nullptr};

CClient_Connection::CClient_Connection(){

}

CClient_Connection::~CClient_Connection() {
    Release();
}

void CClient_Connection::Initialize()
{
	senderThread = std::thread(&CClient_Connection::SendThread, this);
	receiverThread = std::thread(&CClient_Connection::ReceiveThread, this);
}

void CClient_Connection::Set_SOCKET(SOCKET sock)
{
	clientSock = sock;
}

void CClient_Connection::Push_RecvQueue(RecvQueue_data data)
{
    std::lock_guard<std::mutex> lock(receiveMutex);
    receiveQueue.emplace(data);
    recvCv.notify_one();

}

void CClient_Connection::ReceiveThread()
{
    while (!m_bTerminateThreads) {
        char buffer[512];
        int retval = recv(clientSock, buffer, sizeof(SendHeaderPacket), 0);
        if (retval == SOCKET_ERROR || retval == 0) {
            std::cout << "헤더 소켓 수신 실패!" << std::endl;
            break;
        }

        SendHeaderPacket headerPacket;
        memcpy(&headerPacket, buffer, sizeof(headerPacket));

        if (headerPacket.length > 0) {
            retval = recv(clientSock, buffer, headerPacket.length, 0);
            if (retval == SOCKET_ERROR || retval == 0) {
                std::cout << "데이터 소켓 수신 실패!" << std::endl;
                break;
            }

            SendQueue_data queueData;
            queueData.event = headerPacket.event;

            size_t dataLength = headerPacket.length;
            if (dataLength > sizeof(queueData.data)) {
                dataLength = sizeof(queueData.data);
            }

            memcpy(queueData.data, buffer, dataLength);

          
            std::lock_guard<std::mutex> lock(receiveMutex);
            sendQueue.push(queueData);
        }
    }
}

void CClient_Connection::SendThread()
{
    while (!m_bTerminateThreads) {
        std::unique_lock<std::mutex> lock(receiveMutex);
        recvCv.wait(lock, [this]() {return !receiveQueue.empty() || m_bTerminateThreads; });
        if (m_bTerminateThreads) break;

        RecvQueue_data Temp = receiveQueue.front();
        receiveQueue.pop();
        lock.unlock();

        RECEIVE_EVENT_TYPE eventType = Temp.event;

        switch (eventType) {
        case R_MY_CLIENT_ID: {
            RecvHeaderPacket headerPacket = { sizeof(R_MY_CLIENT_ID),R_MY_CLIENT_ID };
            int retval = send(clientSock, reinterpret_cast<char*>(&headerPacket), sizeof(headerPacket), 0);

            R_SetClientPacket packet;
            memcpy(&packet, Temp.data, sizeof(R_SetClientPacket));
            retval = send(clientSock, reinterpret_cast<char*>(&packet), sizeof(packet), 0);

            cout << "플레이어" << "선택 정보 전송" << endl;
            cout << "클라이언트 " << myID << "에게 보냄" << Temp.data[0];

        }
            break;

        case R_PLAYER_CHOICE:
        {
            RecvHeaderPacket headerPacket = { sizeof(R_PlayerChoicePacket),R_PLAYER_CHOICE };
            int retval = send(clientSock, reinterpret_cast<char*>(&headerPacket), sizeof(headerPacket), 0);

            R_PlayerChoicePacket packet;
            packet.Choiced_Character = Temp.data[0];
            retval = send(clientSock, reinterpret_cast<char*>(&packet), sizeof(packet), 0);


        }
            break;
        case R_LEVEL_CHANGE: {
            RecvHeaderPacket headerPacket = { sizeof(R_LevelChangePacket),R_LEVEL_CHANGE };
            int retval = send(clientSock, reinterpret_cast<char*>(&headerPacket), sizeof(headerPacket), 0);

            R_LevelChangePacket packet;
            packet.Level = Temp.data[0];
            retval = send(clientSock, reinterpret_cast<char*>(&packet), sizeof(packet), 0);

            cout << "레벨 변경 데이터 전송" << endl;
        }
        case R_OTHER_PLAYER_MOVE: {

            RecvHeaderPacket headerPacket = { sizeof(R_Other_Player_MovePacket),R_OTHER_PLAYER_MOVE };
            int retval = send(clientSock, reinterpret_cast<char*>(&headerPacket), sizeof(headerPacket), 0);
            R_Other_Player_MovePacket packet;
            memcpy(&packet, Temp.data, sizeof(R_Other_Player_MovePacket));
            retval = send(clientSock, reinterpret_cast<char*>(&packet), sizeof(packet), 0);
            

        }
             break;
        case R_MONSTER_GEN: {

            RecvHeaderPacket headerPacket = { sizeof(R_MonsterInitPosPacket),R_MONSTER_GEN };
            int retval = send(clientSock, reinterpret_cast<char*>(&headerPacket), sizeof(headerPacket), 0);
            R_MonsterInitPosPacket packet;
            memcpy(&packet, Temp.data, sizeof(R_MonsterInitPosPacket));
            retval = send(clientSock, reinterpret_cast<char*>(&packet), sizeof(packet), 0);

        }

            break;
        case R_OBJ_DEAD:
        {
            RecvHeaderPacket headerPacket = { sizeof(R_MonsterDeadPacket),R_OBJ_DEAD };
            int retval = send(clientSock, reinterpret_cast<char*>(&headerPacket), sizeof(headerPacket), 0);
            R_MonsterDeadPacket packet;
            memcpy(&packet, Temp.data, sizeof(R_MonsterDeadPacket));
            retval = send(clientSock, reinterpret_cast<char*>(&packet), sizeof(packet), 0);
        }
            break;
        default:
            
            break;
        }

    }

}

void CClient_Connection::Release()
{
    m_bTerminateThreads = true;
    
    recvCv.notify_all();
    sendCv.notify_all();
}


bool CClient_Connection::Get_SendQueueData(SendQueue_data& data)
{
    if (sendQueue.empty()) {
        return false;
    }

    data = sendQueue.front();
    sendQueue.pop();
    return true;
}

void CClient_Connection::Lock_SendQueue()
{
    sendMutex.lock();
}

void CClient_Connection::Unlock_SendQueue()
{
    sendMutex.unlock();
}
