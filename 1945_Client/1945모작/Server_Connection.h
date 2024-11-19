#pragma once
#include "Define.h"

class CServer_Connection
{
public:
	CServer_Connection();
	~CServer_Connection();

public:
	void Initialize(const char* ServerIP);
	void Send_Data(SEND_EVENT_TYPE eEvent, void* Data);
	ReceiveDataResult Receive_Data();
	void Release();

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

	static	CServer_Connection* m_pInstance;
	SOCKET						sock;


};

