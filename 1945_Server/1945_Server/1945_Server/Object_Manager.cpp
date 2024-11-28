#include "pch.h"
#include "Object_Manager.h"
#include "Collision_Manager.h"
#include "Client_Connection.h"

CObject_Manager* CObject_Manager::m_pInstance = nullptr;

CObject_Manager::CObject_Manager()
{
}

CObject_Manager::~CObject_Manager()
{
	Release();
}

void CObject_Manager::Add_Object(OBJ_ID eID, CGameObject* pGameObject)
{
	if (OBJ_END <= eID || nullptr == pGameObject)
		return;

	m_ObjectList[eID].push_back(pGameObject);
}

int CObject_Manager::Update(void)
{

	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_ObjectList[i].begin();
			iter != m_ObjectList[i].end(); )
		{
			int iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				if (i == OBJ_ENEMY) {
					for (int i = 0; i < CLIENT_END; ++i) {

						RecvQueue_data DeadMonsterData;
						DeadMonsterData.event = R_OBJ_DEAD;

						R_MonsterDeadPacket DeadMonsterPacket;
						DeadMonsterPacket.MonsterID = (uint8_t)dynamic_cast<CGameObject*>(*iter)->Get_OBJID();
						memcpy(DeadMonsterData.data, &DeadMonsterPacket, sizeof(R_MonsterDeadPacket));
						CClient_Connection::Get_Instance((CLIENT_ID)i)->Push_RecvQueue(DeadMonsterData);
						
					}
					++DeadMonsterCnt;

					if (dynamic_cast<CGameObject*>(*iter)->GetType()) {
						++Monster1Cnt;
					}
					else if (!dynamic_cast<CGameObject*>(*iter)->GetType()) {
						++Monster2Cnt;
					}
				}

				
				Safe_Delete<CGameObject*>(*iter);
				iter = m_ObjectList[i].erase(iter);


			}
			else
				++iter;
		}
	}

	cout << "제거된 몬스터 수 : " << DeadMonsterCnt << " 개" << endl;
	cout << "제거된 작은 몬스터 수 : " << Monster1Cnt << " 개" << endl;
	cout << "제거된 큰 몬스터 수 : " << Monster2Cnt << " 개" << endl;
	return 0;
}

void CObject_Manager::Late_Update(void)
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjectList[i])
		{
			iter->Late_Update();

			if (m_ObjectList[i].empty())
				break;

		}
	}

	CCollision_Manager::Collision_MyBullet(m_ObjectList[OBJ_PLAYERBULLET], m_ObjectList[OBJ_ENEMY]);
	if (!CObject_Manager::Get_Instance()->List_Empty(OBJ_BOSSPART)) {
		CCollision_Manager::Collision_MyBullet(m_ObjectList[OBJ_PLAYERBULLET], m_ObjectList[OBJ_BOSSPART]);
	}
}

void CObject_Manager::Release(void)
{

	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for_each(m_ObjectList[i].begin(), m_ObjectList[i].end(), Safe_Delete<CGameObject*>);
		m_ObjectList[i].clear();
	}
}

void CObject_Manager::DeleteID(OBJ_ID eID)
{
	for (auto& iter : m_ObjectList[eID])
		Safe_Delete(iter);

	m_ObjectList[eID].clear();
}
