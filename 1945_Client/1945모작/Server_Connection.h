#pragma once
#include "Define.h"
#include <thread>
#include <mutex>
#include <condition_variable>

class CServer_Connection
{
public:
	CServer_Connection();
	~CServer_Connection();

public:
	void Initialize(const char* ServerIP);
	void Push_SendQueue(SendQueue_data);
	void ReceiveThread();
	void SendThread();
	void Release();

	void Lock_RecvQueue();
	void Unlock_RecvQueue();

	
	bool RecvQueueEmpty() {
		if (receiveQueue.empty())
			return true;
		else
			return false;

	}
	bool Get_RecvQueueData(RecvQueue_data& data);

	void Clear_Recv_Queue(){
		while (!receiveQueue.empty()) {
			receiveQueue.pop();
		}
	}
public:
	static	CServer_Connection* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CServer_Connection;
		}
		return m_pInstance;
	}

	static void			Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:

	queue<SendQueue_data> sendQueue;
	queue<RecvQueue_data> receiveQueue;



	static	CServer_Connection* m_pInstance;
	SOCKET						sock;
	int							m_iMY_CLIENTID;
	bool m_bTerminateThreads = false;

	thread senderThread;         // 송신 스레드
	thread receiverThread;       // 수신 스레드
	condition_variable			sendCv;  // 송신 대기를 위한 조건 변수
	mutex						sendMutex;
	mutex						receiveMutex;
	mutex						TempMutex;

};

