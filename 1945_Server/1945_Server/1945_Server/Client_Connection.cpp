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

void CClient_Connection::Push_SendQueue()
{

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
            cout << "데이터 수신 성공" << endl;
        }
    }
}

void CClient_Connection::SendThread()
{


}

void CClient_Connection::Release()
{
}

void CClient_Connection::Receive_Data()
{
    
}
