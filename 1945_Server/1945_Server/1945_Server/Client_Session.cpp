#include "Client_Session.h"
#include <iostream>
#include <cstring>

ClientSession::ClientSession(SOCKET clientSocket, int clientIndex)
    : clientSocket(clientSocket), clientIndex(clientIndex), running(true) {
}

ClientSession::~ClientSession() {
    Stop();
}

void ClientSession::Start() {
    recvThread = std::thread(&ClientSession::ReceiveData, this);
    sendThread = std::thread(&ClientSession::SendData, this);
}

void ClientSession::Stop() {
    running = false;
    if (recvThread.joinable()) {
        recvThread.join();
    }
    if (sendThread.joinable()) {
        sendThread.join();
    }
    closesocket(clientSocket);
}

void ClientSession::ReceiveData() {
    char recvBuffer[1024];  // 데이터를 받을 버퍼
    int recvSize;

    while (running) {
        // 첫 번째 recv()에서 헤더를 받음
        recvSize = recv(clientSocket, recvBuffer, sizeof(SendHeaderPacket), 0);
        if (recvSize == SOCKET_ERROR) {
            continue;
        }
        else if (recvSize == 0) {
            std::cout << "클라이언트 " << clientIndex << " 연결 종료\n";
            break;
        }

        SendHeaderPacket header;
        memcpy(&header, recvBuffer, sizeof(SendHeaderPacket)); // 헤더 복사

        // 헤더의 length 값만큼 본문 데이터를 추가로 받음
        char* dataBuffer = new char[header.length];
        recvSize = recv(clientSocket, dataBuffer, header.length, 0);
        if (recvSize == SOCKET_ERROR) {
            delete[] dataBuffer;
            continue;
        }
        else if (recvSize == 0) {
            std::cout << "클라이언트 " << clientIndex << " 연결 종료\n";
            delete[] dataBuffer;
            break;
        }

        // 수신한 데이터를 처리하는 로직
        switch (header.event) {
        case S_PLAYER_CHOICE: {
            S_PlayerChoicePacket* playerChoice = reinterpret_cast<S_PlayerChoicePacket*>(dataBuffer);
            if (clientIndex == 0) {
                P1.index = playerChoice->Choiced_Character;
            }
            else if (clientIndex == 1) {

                P2.index = playerChoice->Choiced_Character;
            }

            break;
        }
        case S_KEY_INPUT: {
            S_KeyInputPacket* keyInput = reinterpret_cast<S_KeyInputPacket*>(dataBuffer);
            // 데이터 처리 로직
            break;
        }
        default:
            std::cout << "알 수 없는 이벤트 타입: " << header.event << std::endl;
            break;
        }

        delete[] dataBuffer; // 동적 메모리 해제
    }
}

void ClientSession::SendData() {
    // 데이터를 전송하는 로직 (이 예제에서는 단순히 빈 함수로 두었습니다)
    // 처리된 데이터를 클라이언트에게 전송할 수 있도록 구현
    while (running) {
        // 예시: 처리된 데이터 전송
        // send(clientSocket, ...);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));  // 대기 시간
    }
}