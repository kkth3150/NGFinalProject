#include "pch.h"
#include "Client_Connection.h"

CClient_Connection* CClient_Connection::m_pInstance[2] = {nullptr,nullptr};


CClient_Connection::CClient_Connection()
{
}

CClient_Connection::~CClient_Connection()
{
}

void CClient_Connection::Initialize(const char* ServerIP)
{
}

void CClient_Connection::Push_SendQueue()
{
}

void CClient_Connection::ReceiveThread()
{
}

void CClient_Connection::SendThread()
{
}

void CClient_Connection::Release()
{
}

ReceiveDataResult CClient_Connection::Receive_Data()
{
	return ReceiveDataResult();
}
