#include "pch.h"
#include "Level_Manager.h"
#include "Server_Connection.h"
#include "Object_Manager.h"
#include "Finger.h"
#include <thread>
#include <mutex>
#include <condition_variable>

CLevel_Manager* CLevel_Manager::m_pInstance = nullptr;
std::mutex g_recvMutex;
std::condition_variable g_dataCondVar;
bool g_hasNewData = false;
ReceiveDataResult g_receivedData;

CLevel_Manager::CLevel_Manager() : m_eCurLevel(LEVEL_GAMEPLAY), m_ePreLevel(LEVEL_END)
{
}

CLevel_Manager::~CLevel_Manager()
{
	Release();
}

void CLevel_Manager::Level_Change(LEVEL_ID eID)
{
	m_eCurLevel = eID;

	if (m_eCurLevel != m_ePreLevel) {
		Safe_Delete(m_pLevel);

		switch (m_eCurLevel) {
		case LEVEL_GAME_END:
			m_pLevel = new CLevel_GameEnd;
			break;

		case LEVEL_MENU:
			m_pLevel = new CLevel_Menu;
			break;

		case LEVEL_GAMEPLAY:
			m_pLevel = new CLevel_GamePlay;
			break;
		}

		m_pLevel->Initialize();
		m_ePreLevel = m_eCurLevel;

	}

}

int CLevel_Manager::Update()
{
	m_pLevel->Update();
	return 0;
}


void CLevel_Manager::Late_Update()
{
	m_pLevel->Late_Update();
}

void CLevel_Manager::Render(HDC hDC)
{
	m_pLevel->Render(hDC);
}

void CLevel_Manager::Release(void)
{
	Safe_Delete(m_pLevel);
}

void CLevel_Manager::ReceiveThread()
{
	while (true) {
		ReceiveDataResult data = CServer_Connection::Get_Instance()->Receive_Data();

		std::unique_lock<std::mutex> lock(g_recvMutex);
		g_receivedData = data;
		g_hasNewData = true;
		lock.unlock();

		g_dataCondVar.notify_one();
	}

}

void CLevel_Manager::ProcessReceivedData()
{

	std::unique_lock<std::mutex> lock(g_recvMutex);
	if (!lock.owns_lock()) {
		return;
	}
	if (!g_hasNewData) {
		return;
	}


	switch (g_receivedData.eventType) {
	case R_PLAYER_CHOICE: {
		if (m_eCurLevel == LEVEL_MENU) {
			R_PlayerChoicePacket* Temp = static_cast<R_PlayerChoicePacket*>(g_receivedData.data);
			dynamic_cast<CFinger*>(CObject_Manager::Get_Instance()->Get_List(OBJ_FINGER)->front())->SetFlight((int)Temp->Choiced_Character_P2);
		}
	}
		break;
	case R_LEVEL_CHANGE:
		// R_LEVEL_CHANGE 이벤트 처리
		break;
	default:
		break;
	}

	g_hasNewData = false;
}
