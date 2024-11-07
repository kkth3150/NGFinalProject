#include "pch.h"
#include "MainGame.h"
#include "Key_Manager.h"
#include "Bmp_Manager.h"
#include "Level_Manager.h"
#include "Object_Manager.h"

CMainGame::CMainGame() : m_dwTime(GetTickCount()), m_iFPS(0)
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS));
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_hDC = GetDC(g_hWnd);

	CBmp_Manager::Get_Instance()->Insert_Bmp(L"../Image/Back.bmp", L"BackBuffer");
	CLevel_Manager::Get_Instance()->Level_Change(LEVEL_MENU);
}

void CMainGame::Update(void)
{
	CLevel_Manager::Get_Instance()->Update();
}

void CMainGame::Late_Update(void)
{
	CLevel_Manager::Get_Instance()->Late_Update();
}

void CMainGame::Render(void)
{
	++m_iFPS;
	if (m_dwTime + 1000 < GetTickCount64())
	{
		swprintf_s(m_szFPS, L"윈도우프로그래밍 기말프로젝트 (1945) FPS : %d", m_iFPS);

		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount64();
	}

#pragma region 이중 버퍼

	HDC	hBackDC = CBmp_Manager::Get_Instance()->Find_Img(L"BackBuffer");
	CLevel_Manager::Get_Instance()->Render(hBackDC);
	BitBlt(m_hDC, 0, 0, WINCX, WINCY, hBackDC, 0, 0, SRCCOPY);

#pragma endregion
}

void CMainGame::Release(void)
{
	
	ReleaseDC(g_hWnd, m_hDC);
}