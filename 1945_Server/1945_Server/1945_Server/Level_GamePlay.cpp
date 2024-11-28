#include "pch.h"
#include "Level_Manager.h"
#include "Level_GamePlay.h"
#include "Client_Connection.h"
#include "Object_Manager.h"
#include "AbstractFactory.h"

#include "Boss.h"
#include "Monster_1.h"
#include "Monster_2.h"
#include "Player1.h"
#include "Player2.h"


#define MAP_SizeY 5353
#define MAP_SizeX 600

CLevel_GamePlay::CLevel_GamePlay()
{
}

CLevel_GamePlay::~CLevel_GamePlay()
{
}

void CLevel_GamePlay::Initialize()
{
    CObject_Manager::Get_Instance()->Add_Object(OBJ_PLAYER1, CAbstractFactory<CPlayer1>::Create());
    CObject_Manager::Get_Instance()->Add_Object(OBJ_PLAYER2, CAbstractFactory<CPlayer2>::Create());

    Player_C1 = dynamic_cast<CPlayer1*>(CObject_Manager::Get_Instance()->Get_Player(CLIENT_1));
    Player_C2 = dynamic_cast<CPlayer2*>(CObject_Manager::Get_Instance()->Get_Player(CLIENT_2));

}

int CLevel_GamePlay::Update()
{
    system("cls");
    cout << "게임플레이 레벨" << endl;
    cout << "player1 좌표 " << "\t\t\t" << "Player2 좌표" << endl;
    cout << "X : " << Player_C1->Get_Info().fX << "\t\t\t\t" << "X : " << Player_C2->Get_Info().fX << endl;
    cout << "Y : " << Player_C1->Get_Info().fY << "\t\t\t\t" << "Y : " << Player_C2->Get_Info().fY << endl << endl << endl;

    cout << "생성된 몬스터 : " << i_MonsterCnt << " 마리 " << endl;

 
    for (int i = 0; i < CLIENT_END; ++i) {

        SendQueue_data data;
        CClient_Connection::Get_Instance((CLIENT_ID)i)->Lock_SendQueue();
        while (!CClient_Connection::Get_Instance((CLIENT_ID)i)->SendQueue_Empty()) {

            CClient_Connection::Get_Instance((CLIENT_ID)i)->Get_SendQueueData(data);
            switch (data.event) {
            case S_INIT_DATA:
            {
                RecvQueue_data Temp;
                Temp.event = R_MY_CLIENT_ID;
                Temp.data[0] = static_cast<uint8_t>(i);
                CClient_Connection::Get_Instance((CLIENT_ID)i)->Push_RecvQueue(Temp);
            }
            break;
            case S_MY_PLAYER_MOVE: {              
                
                float fx = *reinterpret_cast<float*>(&data.data[0]);
                float fy = *reinterpret_cast<float*>(&data.data[4]);

                if (i == CLIENT_1) {
                    Player_C1->Set_Pos(fx, fy);
                }
                else if (i == CLIENT_2) {
                    Player_C2->Set_Pos(fx, fy);
                }


            }
            break;
            default:
                break;

            }

        }
        CClient_Connection::Get_Instance((CLIENT_ID)i)->Unlock_SendQueue();
    }

  
   

    if (m_iMap_Update > MAP_SizeY - WINCY - 1200 && !m_bBossGen) {
        if (CObject_Manager::Get_Instance()->List_Empty(OBJ_ENEMY)) {
            m_bBossGen = true;
            cout << "================보스 생성===================" << endl;
            CObject_Manager::Get_Instance()->Add_Object(OBJ_BOSS, CAbstractFactory<CBoss>::Create());
        }
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
            float TempX = rand() % 600;
            CObject_Manager::Get_Instance()->Add_Object(OBJ_ENEMY, CAbstractFactory<CMonster_2>::Create(TempX, 0, i_MonsterCnt,false));
            ++i_MonsterCnt;
            RecvQueue_data MonsterGenData;
            MonsterGenData.event = R_MONSTER_GEN;
            R_MonsterInitPosPacket MonsterInitPacket;
            MonsterInitPacket.Kind = 0;
            MonsterInitPacket.fx = TempX;
            MonsterInitPacket.fy = 0;
            memcpy(MonsterGenData.data, &MonsterInitPacket, sizeof(R_MonsterInitPosPacket));
            for (int i = 0; i < CLIENT_END; ++i) {
                CClient_Connection::Get_Instance((CLIENT_ID)i)->Push_RecvQueue(MonsterGenData);
            }

        }
        if ((GetTickCount64() - Enemy_Count) % 2000 == 0) {
            float TempX = rand() % 600;
            CObject_Manager::Get_Instance()->Add_Object(OBJ_ENEMY, CAbstractFactory<CMonster_1>::Create(TempX, 0, i_MonsterCnt, true));
            ++i_MonsterCnt;

            RecvQueue_data MonsterGenData;
            MonsterGenData.event = R_MONSTER_GEN;
            R_MonsterInitPosPacket MonsterInitPacket;
            MonsterInitPacket.Kind = 1;
            MonsterInitPacket.fx = TempX;
            MonsterInitPacket.fy = 0;
            memcpy(MonsterGenData.data, &MonsterInitPacket, sizeof(R_MonsterInitPosPacket));
            for (int i = 0; i < CLIENT_END; ++i) {
                CClient_Connection::Get_Instance((CLIENT_ID)i)->Push_RecvQueue(MonsterGenData);
            }

        }
    }


    CObject_Manager::Get_Instance()->Update();
	return 0;
}

void CLevel_GamePlay::Late_Update()
{
      
    for (int i = 0; i < CLIENT_END; ++i) {

        if (i == CLIENT_1) {
            RecvQueue_data PlayerMoveQueueData1;
            PlayerMoveQueueData1.event = R_OTHER_PLAYER_MOVE;

            R_Other_Player_MovePacket PlayerMoveData1;
            PlayerMoveData1.fx = Player_C2->Get_Info().fX;
            PlayerMoveData1.fy = Player_C2->Get_Info().fY;
 
            memcpy(PlayerMoveQueueData1.data, &PlayerMoveData1, sizeof(R_Other_Player_MovePacket));

            CClient_Connection::Get_Instance((CLIENT_ID)i)->Push_RecvQueue(PlayerMoveQueueData1);
        }
       
        if (i == CLIENT_2) {
            RecvQueue_data RecvQueueData2;
            RecvQueueData2.event = R_OTHER_PLAYER_MOVE;

            R_Other_Player_MovePacket PlayerMoveData2;
            PlayerMoveData2.fx = Player_C1->Get_Info().fX;
            PlayerMoveData2.fy = Player_C1->Get_Info().fY;

            memcpy(RecvQueueData2.data, &PlayerMoveData2, sizeof(R_Other_Player_MovePacket));
            CClient_Connection::Get_Instance((CLIENT_ID)i)->Push_RecvQueue(RecvQueueData2);
        }
        
    }


    CObject_Manager::Get_Instance()->Late_Update();
}

void CLevel_GamePlay::Release(void)
{
    CObject_Manager::Get_Instance()->DeleteID(OBJ_PLAYER1);
    CObject_Manager::Get_Instance()->DeleteID(OBJ_PLAYER2);
    CObject_Manager::Get_Instance()->DeleteID(OBJ_PLAYERBULLET);
}

void CLevel_GamePlay::ShowText(const char* Text, int iTime)
{


}
