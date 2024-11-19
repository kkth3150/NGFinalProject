#pragma once
#ifndef CLIENTSESSION_H
#define CLIENTSESSION_H
#include "ErrorMsg.h"
#include <thread>
#include <condition_variable>
#include <mutex>
#include "Define.h"

class ClientSession {
public:
    ClientSession(SOCKET clientSocket, int clientIndex);
    ~ClientSession();

    void Start();
    void Stop();

private:
    void ReceiveData();   // 데이터를 수신하는 함수
    void SendData();      // 데이터를 전송하는 함수

    SOCKET clientSocket;  // 클라이언트 소켓
    int clientIndex;      // 클라이언트 인덱스

    std::thread recvThread;  // 데이터 수신 쓰레드
    std::thread sendThread;  // 데이터 전송 쓰레드

    bool running;         // 세션 상태
    std::mutex mtx;       // 동기화를 위한 뮤텍스
    std::condition_variable cv;  // 이벤트 관리


    struct PlayerChoiceData {

        uint8_t index;

    };

    PlayerChoiceData P1;
    PlayerChoiceData P2;

};

#endif // CLIENTSESSION_H