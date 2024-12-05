#include "pch.h"
#include "Level_GameEnd.h"
#include "Bmp_Manager.h"
#include "Level_Manager.h"
#include "Server_Connection.h"
#include "UI.h"
#include "AbstractFactory.h"
#include "Object_Manager.h"

CLevel_GameEnd::CLevel_GameEnd()
{
}

CLevel_GameEnd::~CLevel_GameEnd()
{
	Release();
}

void CLevel_GameEnd::Initialize()
{
	CBmp_Manager::Get_Instance()->Insert_Bmp(L"../Image/Menu/GAME_CLEAR(600X900).bmp", L"GAME_CLEAR");
	CBmp_Manager::Get_Instance()->Insert_Bmp(L"../Image/UI/Score(47X47X10).bmp", L"SCORE");

	CGameObject* pScoreUI_P1 = CAbstractFactory<CUI>::Create_UI(190.f, 380.f, 460.f, 46.f);
	pScoreUI_P1->Set_FrameKey(L"SCORE");
	dynamic_cast<CUI*>(pScoreUI_P1)->Set_State(UI_END_SCORE);
	dynamic_cast<CUI*>(pScoreUI_P1)->Set_ScoreUI(P1_SCORE);
	CObject_Manager::Get_Instance()->Add_Object(OBJ_UI, pScoreUI_P1);

	CGameObject* pScoreUI_P2= CAbstractFactory<CUI>::Create_UI(190.f, 650.f, 460.f, 46.f);
	pScoreUI_P2->Set_FrameKey(L"SCORE");
	dynamic_cast<CUI*>(pScoreUI_P2)->Set_State(UI_END_SCORE);
	dynamic_cast<CUI*>(pScoreUI_P1)->Set_ScoreUI(P2_SCORE);
	CObject_Manager::Get_Instance()->Add_Object(OBJ_UI, pScoreUI_P2);
}

int CLevel_GameEnd::Update()
{
	CObject_Manager::Get_Instance()->Update();
	return 0;
}


void CLevel_GameEnd::Late_Update()
{
}

void CLevel_GameEnd::Render(HDC hDC)
{

	HDC	hMemDC = CBmp_Manager::Get_Instance()->Find_Img(L"GAME_CLEAR");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
	CObject_Manager::Get_Instance()->Render(hDC);
}

void CLevel_GameEnd::Release(void)
{
}
