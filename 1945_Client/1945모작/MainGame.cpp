#include "pch.h"
#include "resource.h"
#include "MainGame.h"
#include "Key_Manager.h"
#include "Bmp_Manager.h"
#include "Level_Manager.h"
#include "Object_Manager.h"
#include "Server_Connection.h"

INT_PTR CALLBACK IPDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

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
	//wchar_t* serverIP = new wchar_t[16]; // 16개의 wchar_t 크기로 메모리 할당
	//if (DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_IP_DIALOG), g_hWnd, IPDialogProc, (LPARAM)serverIP) == IDOK)
	//{
	//	// 입력받은 IP 주소를 char*로 변환
	//	char ipBuffer[16];
	//	size_t convertedChars = 0;

	//	// wcstombs_s 사용하여 IP 주소 변환
	//	wcstombs_s(&convertedChars, ipBuffer, sizeof(ipBuffer), serverIP, _TRUNCATE);

	//	// 서버 초기화
	//	CServer_Connection::Get_Instance()->Initialize(ipBuffer);
	//}
	//else
	//{
	//	MessageBox(g_hWnd, L"Server IP was not provided.", L"Error", MB_OK | MB_ICONERROR);
	//}

	//// 메모리 해제
	//delete[] serverIP;
	CServer_Connection::Get_Instance()->Initialize("127.168.0.1");
	CBmp_Manager::Get_Instance()->Insert_Bmp(L"../Image/Back.bmp", L"BackBuffer");
	CLevel_Manager::Get_Instance()->Level_Change(LEVEL_MENU);

}

void CMainGame::Update(void)
{
	CLevel_Manager::Get_Instance()->Update();
}

void CMainGame::Recv_Data(void)
{
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
	if (m_recvThread.joinable()) {
		m_recvThread.join();  // 수신 스레드 종료 대기
	}
	ReleaseDC(g_hWnd, m_hDC);
}

INT_PTR CALLBACK IPDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			// IP 주소를 얻기 위해 텍스트 박스의 내용을 가져옴
			wchar_t ip[16];
			GetDlgItemText(hDlg, IDC_IP_EDIT, ip, 16);

			// IP 주소를 전달
			SetWindowLongPtr(hDlg, GWLP_USERDATA, (LONG_PTR)_wcsdup(ip));
			EndDialog(hDlg, IDOK);
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, IDCANCEL);
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}