#include "pch.h"
#include "Key_Manager.h"

CKey_Manager* CKey_Manager::m_pInstance = nullptr;

CKey_Manager::CKey_Manager()
{
	ZeroMemory(m_bKeyState, sizeof(m_bKeyState));
}

CKey_Manager::~CKey_Manager()
{
}

bool CKey_Manager::Key_Pressing(int _iKey)
{
	if (GetAsyncKeyState(_iKey) & 0x8000)
		return true;

	return false;
}

bool CKey_Manager::Key_Down(int _iKey)
{
	if (!m_bKeyState[_iKey] && (GetAsyncKeyState(_iKey) & 0x8000))
	{
		m_bKeyState[_iKey] = !m_bKeyState[_iKey];
		return true;
	}

	for (int i = 0; i < VK_MAX; ++i)
	{
		if (m_bKeyState[i] && !(GetAsyncKeyState(_iKey) & 0x8000))
			m_bKeyState[i] = !m_bKeyState[i];
	}

	return false;
}

bool CKey_Manager::Key_Up(int _iKey)
{
	if (m_bKeyState[_iKey] && !(GetAsyncKeyState(_iKey) & 0x8000))
	{
		m_bKeyState[_iKey] = !m_bKeyState[_iKey];
		return true;
	}

	for (int i = 0; i < VK_MAX; ++i)
	{
		if (!m_bKeyState[i] && (GetAsyncKeyState(_iKey) & 0x8000))
			m_bKeyState[i] = !m_bKeyState[i];
	}



	return false;
}
