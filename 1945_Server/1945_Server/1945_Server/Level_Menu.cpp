#include "pch.h"
#include "Level_Manager.h"
#include "Level_Menu.h"
#include "Client_Connection.h"

CLevel_Menu::CLevel_Menu()
{
}

CLevel_Menu::~CLevel_Menu()
{
    Release();
}

void CLevel_Menu::Initialize()
{
}

int CLevel_Menu::Update()
{
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
            case S_PLAYER_CHOICE: {
                RecvQueue_data Temp;
                Temp.event = R_PLAYER_CHOICE;
                Temp.data[0] = data.data[0];
                if (i == CLIENT_1) {

                    CClient_Connection::Get_Instance(CLIENT_2)->Push_RecvQueue(Temp);
                }
                if (i == CLIENT_2) {

                    CClient_Connection::Get_Instance(CLIENT_1)->Push_RecvQueue(Temp);
                }
                
                cout << "플레이어 " << i << "선택정보 수신" << endl;
            }
                break;
           
            case S_START: {

                if (i == CLIENT_1)
                    Flag[CLIENT_1] = true;
                
                if (i == CLIENT_2)
                    Flag[CLIENT_2] = true;

            }
                        break;
            default:
                break;

            }

        }
        CClient_Connection::Get_Instance((CLIENT_ID)i)->Unlock_SendQueue();
    }

    return 0;
}

void CLevel_Menu::Late_Update()
{
    int temp = 0;
    for (int i = 0; i < CLIENT_END; ++i) {
        if (Flag[i])
            ++temp;
    }
    
    if (temp == CLIENT_END) {

        for (int i = 0; i < CLIENT_END; ++i) {
            RecvQueue_data Temp;
            Temp.event = R_LEVEL_CHANGE;
            Temp.data[0] = static_cast<uint8_t>(LEVEL_GAMEPLAY);
            CClient_Connection::Get_Instance((CLIENT_ID)i)->Push_RecvQueue(Temp);
            
        }
        CLevel_Manager::Get_Instance()->Level_Change(LEVEL_GAMEPLAY);
        cout << "===============게임플레이 레벨======================" << endl;
    }
}

void CLevel_Menu::Release(void)
{
}
