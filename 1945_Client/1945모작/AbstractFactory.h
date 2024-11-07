#pragma once
#include "GameObject.h"
#include "Boss_Posin.h"
#include "Boss_Gun.h"
#include "Boss_Bullet.h"

template<typename T>
class CAbstractFactory
{
public:
	CAbstractFactory() {}
	~CAbstractFactory() {}

public:
	static CGameObject* Create()
	{
		CGameObject* pGameObject = new T;
		pGameObject->Initialize();

		return pGameObject;
	}

	static CGameObject* Create(float fX, float fY)
	{
		CGameObject* pGameObject = new T;
		pGameObject->Set_Pos(fX, fY);
		pGameObject->Initialize();

		return pGameObject;
	}

	static CGameObject* Create(float fX, float fY, DIRECTION eDir)
	{
		CGameObject* pGameObject = new T;

		pGameObject->Set_Pos(fX, fY);
		pGameObject->Initialize();


		pGameObject->Set_Direction(eDir);
		return pGameObject;
	}


	static CGameObject* Create_UI(float fX, float fY, float fCX, float fCY,int Frames,DWORD FrameSpeed)
	{
		CGameObject* pGameObject = new T;
		pGameObject->Set_Pos(fX, fY);
		pGameObject->Set_Size(fCX, fCY);
		pGameObject->Set_Frame(Frames, FrameSpeed);
		pGameObject->Initialize();

		return pGameObject;
	}

	static CGameObject* Create_UI(float fX, float fY, float fCX, float fCY)
	{
		CGameObject* pGameObject = new T;
		pGameObject->Set_Pos(fX, fY);
		pGameObject->Set_Size(fCX, fCY);
		pGameObject->Initialize();

		return pGameObject;
	}

	static CGameObject* CreatePlayerBullet(float fX, float fY, PLAYER_BULLET eBullet)
	{
		CGameObject* pGameObject = new T;
		pGameObject->Set_Pos(fX, fY);
		dynamic_cast<CPlayer_Bullet*>(pGameObject)->Set_BulletKind(eBullet);
		pGameObject->Initialize();
	

		return pGameObject;
	}


	static CGameObject* CreateBossBullet(float fX, float fY,float DirX, float DirY, int iBulletKind)
	{
		CGameObject* pGameObject = new T;
		pGameObject->Set_Pos(fX, fY);
		dynamic_cast<CBoss_Bullet*>(pGameObject)->Set_BOSS_BulletKind(iBulletKind);
		dynamic_cast<CBoss_Bullet*>(pGameObject)->Set_Direction(DirX, DirY);
		pGameObject->Initialize();


		return pGameObject;
	}

	static CGameObject* CreatePosin(int iPos)
	{
		CGameObject* pGameObject = new T;
		dynamic_cast<CBoss_Posin*>(pGameObject)->Set_PosinPos(iPos);
		pGameObject->Initialize();


		return pGameObject;
	}

	static CGameObject* CreateGun(int iNum)
	{
		CGameObject* pGameObject = new T;
		dynamic_cast<CBoss_Gun*>(pGameObject)->Set_Gun_Index(iNum);
		pGameObject->Initialize();


		return pGameObject;
	}

	static CGameObject* Create(float fX, float fY, float fAngle)
	{
		CGameObject* pGameObject = new T;
		pGameObject->Initialize();
		pGameObject->Set_Pos(fX, fY);
		pGameObject->Set_Angle(fAngle);

		return pGameObject;
	}

	static CGameObject* CreateEnemyBullet(float fX, float fY, ENEMY_BULLET eBullet)
	{
		CGameObject* pGameObject = new T;
		pGameObject->Set_Pos(fX, fY);
		dynamic_cast<CEnemy_Bullet*>(pGameObject)->Set_BulletKind(eBullet);
		pGameObject->Initialize();


		return pGameObject;
	}
};

