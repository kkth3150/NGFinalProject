#pragma once
#include "Define.h"

class CKey_Manager
{
private:
	CKey_Manager();
	~CKey_Manager();

public:
	bool		Key_Pressing(int _iKey);
	bool		Key_Down(int _iKey);
	bool		Key_Up(int _iKey);

public:
	static	CKey_Manager* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CKey_Manager;
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
	static	CKey_Manager* m_pInstance;
	bool		m_bKeyState[VK_MAX];

};
