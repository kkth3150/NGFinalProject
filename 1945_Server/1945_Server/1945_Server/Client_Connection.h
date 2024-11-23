#pragma once
#include "Define.h"


class CClient_Connection
{
public:
	CClient_Connection();
	~CClient_Connection();
public:
	void Initialize(const char* ServerIP);
	void Push_SendQueue();
	void ReceiveThread();
	void SendThread();
	void Release();

	ReceiveDataResult Receive_Data();


public:
	static	CClient_Connection* Get_Instance(CLIENT_ID ID)
	{
		if ((int)ID < 0 || (int)ID >= CLIENT_END) {
			return nullptr;  // 유효하지 않은 인덱스 처리
		}

		if (!m_pInstance[ID]) {
			m_pInstance[ID] = new CClient_Connection;
		}
		return m_pInstance[ID];
	}

	static void Destroy_Instance()
	{
		for (int i = 0; i < CLIENT_END; ++i) {
			if (m_pInstance[i]) {
				delete m_pInstance[i];
				m_pInstance[i] = nullptr;
			}
		}
	}
private:
	static CClient_Connection* m_pInstance[CLIENT_END];

	SOCKET						sock;
	thread senderThread;         // 송신 스레드
	thread receiverThread;       // 수신 스레드
	condition_variable			sendCv;  // 송신 대기를 위한 조건 변수
	mutex						sendMutex;
	mutex						receiveMutex;

	
};

