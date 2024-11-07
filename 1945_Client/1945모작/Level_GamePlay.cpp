#include "pch.h"
#include "Player.h"
#include "Boss.h"
#include "Bmp_Manager.h"
#include "Object_Manager.h"
#include "Level_GamePlay.h"
#include "AbstractFactory.h"
#include "UI.h"
#include "Enemy_1.h"
#include "Enemy_2.h"
#include "Level_Manager.h"

#define MAP_SizeY 5353
#define MAP_SizeX 600

CLevel_GamePlay::CLevel_GamePlay()
{
}

CLevel_GamePlay::~CLevel_GamePlay()
{
	Release();
}

void CLevel_GamePlay::Initialize()
{

	CBmp_Manager::Get_Instance()->Insert_Bmp(L"../Image/Map/Stage_A1.bmp", L"STAGE_A");
	CBmp_Manager::Get_Instance()->Insert_Bmp(L"../Image/UI/Score(47X47X10).bmp", L"SCORE");
	CBmp_Manager::Get_Instance()->Insert_Bmp(L"../Image/UI/Life(30X40X4).bmp", L"LIFE");
	END_Time = 3000;

	CObject_Manager::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());
	
	
	CGameObject* pScoreUI = CAbstractFactory<CUI>::Create_UI(0.f, 0.f, 460.f, 46.f);
	pScoreUI->Set_FrameKey(L"SCORE");
	dynamic_cast<CUI*>(pScoreUI)->Set_State(UI_SCORE);
	CObject_Manager::Get_Instance()->Add_Object(OBJ_UI, pScoreUI);

	CGameObject* pLifeUI = CAbstractFactory<CUI>::Create_UI(0.f, 0.f, 120.f, 40.f);
	pLifeUI->Set_FrameKey(L"LIFE");
	dynamic_cast<CUI*>(pLifeUI)->Set_State(UI_LIFE);
	CObject_Manager::Get_Instance()->Add_Object(OBJ_UI, pLifeUI);

	Enemy_Count = GetTickCount64();

}

int CLevel_GamePlay::Update()
{
	

	if (m_iMap_Update > MAP_SizeY - WINCY - 1200 && !m_bBossGen) {
		m_bBossGen = true;
		CObject_Manager::Get_Instance()->Add_Object(OBJ_BOSS, CAbstractFactory<CBoss>::Create());
	}
	else if (m_bBossGen && !m_bBossDead) {
		if (CObject_Manager::Get_Instance()->List_Empty(OBJ_BOSSPART)) {
			m_bBossDead = true;
			Timer = GetTickCount64();
		}
		
	}
	else if (m_bBossGen && m_bBossDead) {
		if (Timer + END_Time < GetTickCount64()) {
			CLevel_Manager::Get_Instance()->Level_Change(LEVEL_GAME_END);
		}
	}
	else {
		++m_iMap_Update;
	}

	if (!m_bBossGen) {
		if ((GetTickCount64() - Enemy_Count) % 3000 == 0) {
			CObject_Manager::Get_Instance()->Add_Object(OBJ_ENEMY_2, CAbstractFactory<CEnemy_2>::Create(rand() % 600, 0));
		}
		if ((GetTickCount64() - Enemy_Count) % 2000 == 0) {
			CObject_Manager::Get_Instance()->Add_Object(OBJ_ENEMY_1, CAbstractFactory<CEnemy_1>::Create(rand() % 600 - 51, rand() % 300 + 51));
		}
	}
	CObject_Manager::Get_Instance()->Update();
	return 0;
}

void CLevel_GamePlay::Late_Update()
{
	CObject_Manager::Get_Instance()->Late_Update();

}

void CLevel_GamePlay::Render(HDC hDC)
{
	HDC	hMemDC = CBmp_Manager::Get_Instance()->Find_Img(L"STAGE_A");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, MAP_SizeY-WINCY-m_iMap_Update, SRCCOPY);
	CObject_Manager::Get_Instance()->Render(hDC);
}

void CLevel_GamePlay::Release(void)
{
	CObject_Manager::Get_Instance()->DeleteID(OBJ_PLAYER);
	CObject_Manager::Get_Instance()->DeleteID(OBJ_PLAYERBULLET);

}