#pragma once
#include "Level_GameEnd.h"
#include "Level_GamePlay.h"
#include "Level_Menu.h"

class CLevel_Manager
{
private:
	CLevel_Manager();
	~CLevel_Manager();

public:
	void Level_Change(LEVEL_ID eID);
	LEVEL_ID GetSceneID() {
		return m_eCurLevel;
	}
	int	 Update();
	void Late_Update();
	void Render(HDC hDC);
	void Release(void);

public:
	static	CLevel_Manager* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CLevel_Manager;
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
	static	CLevel_Manager*			m_pInstance;
	CLevel*							m_pLevel = nullptr;
	LEVEL_ID						m_ePreLevel;
	LEVEL_ID						m_eCurLevel;
};

