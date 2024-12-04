#include "pch.h"

#include "Boss.h"
#include "Bmp_Manager.h"
#include "Object_Manager.h"
#include "Level_GamePlay.h"
#include "AbstractFactory.h"
#include "UI.h"
#include "Enemy_1.h"
#include "Enemy_2.h"
#include "Level_Manager.h"
#include "Server_Connection.h"
#include "Collision_Manager.h"

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

	CObject_Manager::Get_Instance()->Add_Object(OBJ_PLAYER1, CAbstractFactory<CPlayer>::Create());
	CObject_Manager::Get_Instance()->Add_Object(OBJ_PLAYER2, CAbstractFactory<CPlayer>::Create());

	
	CGameObject* pScoreUI = CAbstractFactory<CUI>::Create_UI(0.f, 0.f, 460.f, 46.f);
	pScoreUI->Set_FrameKey(L"SCORE");
	dynamic_cast<CUI*>(pScoreUI)->Set_State(UI_SCORE);
	CObject_Manager::Get_Instance()->Add_Object(OBJ_UI, pScoreUI);

	CGameObject* pLifeUI = CAbstractFactory<CUI>::Create_UI(0.f, 0.f, 120.f, 40.f);
	pLifeUI->Set_FrameKey(L"LIFE");
	dynamic_cast<CUI*>(pLifeUI)->Set_State(UI_LIFE);
	CObject_Manager::Get_Instance()->Add_Object(OBJ_UI, pLifeUI);

	Enemy_Count = GetTickCount64();

	My_Player = dynamic_cast<CPlayer*>(CObject_Manager::Get_Instance()->Get_Player(PLAYER_1));
	My_Player->Set_My_Player();
	Other_Player = dynamic_cast<CPlayer*>(CObject_Manager::Get_Instance()->Get_Player(PLAYER_2));
}

int CLevel_GamePlay::Update()
{
	
	CObject_Manager::Get_Instance()->Update();

	if (m_bBossGen && !m_bBossDead) {
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

	RecvQueue_data data;
	CServer_Connection::Get_Instance()->Lock_RecvQueue();
	while (!CServer_Connection::Get_Instance()->RecvQueueEmpty()) {

		CServer_Connection::Get_Instance()->Get_RecvQueueData(data);
		switch (data.event) {
		case R_OTHER_PLAYER_MOVE: {

			float fx = *reinterpret_cast<float*>(&data.data[0]);
			float fy = *reinterpret_cast<float*>(&data.data[4]); 
			int	key = *reinterpret_cast<float*>(&data.data[8]);
			Other_Player->SetX(fx);
			Other_Player->SetY(fy);
		}
			break;
		
		case R_MONSTER_GEN: {
			int ID = *reinterpret_cast<int*>(&data.data[0]);
			float fx = *reinterpret_cast<float*>(&data.data[4]);

			if (ID == 0) {
				CObject_Manager::Get_Instance()->Add_Object(OBJ_ENEMY, CAbstractFactory<CEnemy_2>::Create(fx, 0, i_MonsterCnt));
				++i_MonsterCnt;
			}
			else if (ID == 1) {
				CObject_Manager::Get_Instance()->Add_Object(OBJ_ENEMY, CAbstractFactory<CEnemy_1>::Create(fx, 0, i_MonsterCnt));
				++i_MonsterCnt;
			}

			
		}
		break;

		case R_OBJ_DEAD: 
		{
			int ID = (int)data.data[0];
			list<CGameObject*>* pEnemyList = CObject_Manager::Get_Instance()->Get_List(OBJ_ENEMY);
			if (!pEnemyList->empty()) {
				for (auto& Src : *pEnemyList) {
					if (Src->Get_OBJID() == ID) {
						Src->Set_Dead();
					}
				}
			}

		}
			break;
		case R_BOSS_GEN:
		{
			m_bBossGen = true;
			CObject_Manager::Get_Instance()->Add_Object(OBJ_BOSS, CAbstractFactory<CBoss>::Create());

		}
		break;

		case R_BOSS_PART_DEAD:
		{
			int ID = (int)data.data[0];
			list<CGameObject*>* pEnemyList = CObject_Manager::Get_Instance()->Get_List(OBJ_BOSSPART);
			if (!pEnemyList->empty()) {
				for (auto& Src : *pEnemyList) {
					if (Src->Get_OBJID() == ID) {
						Src->Set_Dead();
					}
				}
			}

		}
		break;
		case R_OTHER_PLAYER_DEAD: {
			Other_Player->SetDie();
		}
			break;

		case R_GAME_OVER: {
			CServer_Connection::Get_Instance()->Clear_Recv_Queue();
			CLevel_Manager::Get_Instance()->Level_Change(LEVEL_GAME_OVER);

		}
		case R_LEVEL_CHANGE:
			CServer_Connection::Get_Instance()->Clear_Recv_Queue();
			CLevel_Manager::Get_Instance()->Level_Change(LEVEL_GAME_END);
			break;


		default:
			break;
		}

	}

	CServer_Connection::Get_Instance()->Unlock_RecvQueue();

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
	CObject_Manager::Get_Instance()->DeleteID(OBJ_PLAYER1);
	CObject_Manager::Get_Instance()->DeleteID(OBJ_PLAYER2);
	CObject_Manager::Get_Instance()->DeleteID(OBJ_PLAYERBULLET);

}