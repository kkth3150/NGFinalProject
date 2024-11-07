#include "pch.h"
#include "Level_Manager.h"

CLevel_Manager* CLevel_Manager::m_pInstance = nullptr;

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
