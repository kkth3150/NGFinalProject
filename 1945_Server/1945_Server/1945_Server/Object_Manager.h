#pragma once
#include "GameObject.h"

class CObject_Manager
{
private:
	CObject_Manager();
	~CObject_Manager();

public:
	void		Add_Object(OBJ_ID eID, CGameObject* pGameObject);
	int			Update(void);
	void		Late_Update(void);
	void		Release(void);

	CGameObject* Get_Player(CLIENT_ID id) {
		if (id == CLIENT_1) {
			if (!List_Empty(OBJ_PLAYER1))
				return m_ObjectList[OBJ_PLAYER1].front();

		}
		else if(id == CLIENT_2) {
			if (!List_Empty(OBJ_PLAYER2))
				return m_ObjectList[OBJ_PLAYER2].front();
		}

		
	}

	list<CGameObject*>* Get_List(OBJ_ID eID) {
		if (!List_Empty(eID))
			return &m_ObjectList[eID];
	}

	bool List_Empty(OBJ_ID eID) {
		if (m_ObjectList[eID].empty() == true) {
			return true;
		}
		else {
			return false;
		}

	};

	void		DeleteID(OBJ_ID eID);

private:

	list<CGameObject*>		m_ObjectList[OBJ_END];

public:
	static	CObject_Manager* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CObject_Manager;
		}
		return m_pInstance;
	}

	static void			Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	static	CObject_Manager* m_pInstance;

	int DeadMonsterCnt = 0;
};

