#include "pch.h"
#include "UI.h"
#include "Button.h"
#include "Level_Manager.h"
#include "Bmp_Manager.h"
#include "Object_Manager.h"
#include "Level_Menu.h"
#include "Level_GamePlay.h"
#include "AbstractFactory.h"

CLevel_Menu::CLevel_Menu()
{
}

CLevel_Menu::~CLevel_Menu()
{
	Release();
}

void CLevel_Menu::Initialize()
{
	CBmp_Manager::Get_Instance()->Insert_Bmp(L"../Image/Menu/MenuBackGround(600X900).bmp", L"BACKGROUND");
	CBmp_Manager::Get_Instance()->Insert_Bmp(L"../Image/Menu/GameName(486X402).bmp", L"GAME_NAME");
	CBmp_Manager::Get_Instance()->Insert_Bmp(L"../Image/Menu/StartButton(201X51X2).bmp", L"START_BUTTON");
	CBmp_Manager::Get_Instance()->Insert_Bmp(L"../Image/Menu/PlayerMenu(528X288X45).bmp", L"MENU_FLIGHT");
	CBmp_Manager::Get_Instance()->Insert_Bmp(L"../Image/Menu/FlightData(150X148).bmp", L"FLIGHT_DATA1");
	CBmp_Manager::Get_Instance()->Insert_Bmp(L"../Image/Menu/FlightData2(220X70).bmp", L"FLIGHT_DATA2");
	CBmp_Manager::Get_Instance()->Insert_Bmp(L"../Image/Menu/FLIGHT_NAME(226X54).bmp", L"FLIGHT_NAME");


	CGameObject* pButton = CAbstractFactory<CButton>::Create(300.f, 600.f);
	pButton->Set_FrameKey(L"START_BUTTON");
	CObject_Manager::Get_Instance()->Add_Object(OBJ_BUTTON,pButton);

	CGameObject* pMainUI = CAbstractFactory<CUI>::Create_UI(300.f, 300.f, 486.f, 402.f);
	pMainUI->Set_FrameKey(L"GAME_NAME");
	dynamic_cast<CUI*>(pMainUI)->Set_State(UI_NONANIM);
	CObject_Manager::Get_Instance()->Add_Object(OBJ_UI, pMainUI);

	m_bButton_Down = false;
	m_bDoOnce = false;
}

int CLevel_Menu::Update()
{
	if (m_bButton_Down&&!m_bDoOnce) {

		CGameObject* pButton = CAbstractFactory<CButton>::Create(300.f, 800.f);
		pButton->Set_FrameKey(L"START_BUTTON");
		CObject_Manager::Get_Instance()->Add_Object(OBJ_BUTTON, pButton);

		CGameObject* pMainUI = CAbstractFactory<CUI>::Create_UI(300.f, 300.f, 528.f, 288.f,44,50);
		pMainUI->Set_FrameKey(L"MENU_FLIGHT");
		dynamic_cast<CUI*>(pMainUI)->Set_State(UI_ANIM);
		CObject_Manager::Get_Instance()->Add_Object(OBJ_UI, pMainUI);

		CGameObject* pDATAUI1 = CAbstractFactory<CUI>::Create_UI(450.f, 550.f, 150.f, 148.f);
		pDATAUI1->Set_FrameKey(L"FLIGHT_DATA1");
		dynamic_cast<CUI*>(pDATAUI1)->Set_State(UI_NONANIM);
		CObject_Manager::Get_Instance()->Add_Object(OBJ_UI, pDATAUI1);

		CGameObject* pDATAUI2 = CAbstractFactory<CUI>::Create_UI(150.f, 550.f, 220.f, 70.f);
		pDATAUI2->Set_FrameKey(L"FLIGHT_DATA2");
		dynamic_cast<CUI*>(pDATAUI2)->Set_State(UI_NONANIM);
		CObject_Manager::Get_Instance()->Add_Object(OBJ_UI, pDATAUI2);

		CGameObject* pFLIGHTNAME = CAbstractFactory<CUI>::Create_UI(150.f, 100.f, 226.f, 54.f);
		pFLIGHTNAME->Set_FrameKey(L"FLIGHT_NAME");
		dynamic_cast<CUI*>(pFLIGHTNAME)->Set_State(UI_NONANIM);
		CObject_Manager::Get_Instance()->Add_Object(OBJ_UI, pFLIGHTNAME);

		m_bDoOnce = true;


	}


	if (!CObject_Manager::Get_Instance()->List_Empty(OBJ_BUTTON)) {

		if (!m_bButton_Down) {
			if (dynamic_cast<CButton*>(CObject_Manager::Get_Instance()->Get_List(OBJ_BUTTON)->front())->GetButtonDown()) {
				dynamic_cast<CButton*>(CObject_Manager::Get_Instance()->Get_List(OBJ_BUTTON)->front())->Set_Dead();
				dynamic_cast<CUI*>(CObject_Manager::Get_Instance()->Get_List(OBJ_UI)->front())->Set_Dead();
				m_bButton_Down = true;
			}
		}
	}

	if (m_bDoOnce) {
		if (dynamic_cast<CButton*>(CObject_Manager::Get_Instance()->Get_List(OBJ_BUTTON)->front())->GetButtonDown())
			CLevel_Manager::Get_Instance()->Level_Change(LEVEL_GAMEPLAY);
	}

	CObject_Manager::Get_Instance()->Update();
	return 0;
}

void CLevel_Menu::Late_Update()
{
	CObject_Manager::Get_Instance()->Late_Update();
}

void CLevel_Menu::Render(HDC hDC)
{
	HDC	hMemDC = CBmp_Manager::Get_Instance()->Find_Img(L"BACKGROUND");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0,0, SRCCOPY);
	CObject_Manager::Get_Instance()->Render(hDC);
}

void CLevel_Menu::Release(void)
{
	CObject_Manager::Get_Instance()->DeleteID(OBJ_BUTTON);
	CObject_Manager::Get_Instance()->DeleteID(OBJ_UI);
}
