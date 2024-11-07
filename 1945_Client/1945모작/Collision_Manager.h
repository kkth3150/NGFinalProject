#pragma once

#include "GameObject.h"

class CCollision_Manager
{
public:
	CCollision_Manager();
	~CCollision_Manager();

public:
	static void Collision_Rect(list<CGameObject*> _Dst, list<CGameObject*> _Src);
	static void Collision_Monster(list<CGameObject*> _Dst, list<CGameObject*> _Src);
	static void Collision_ITEM(list<CGameObject*> _Dst, list<CGameObject*> _Src);
	static void Collision_Bomb_ITEM(list<CGameObject*> _Dst, list<CGameObject*> _Src);
	static void Collision_MyBullet(list<CGameObject*> _Dst, list<CGameObject*> _Src);
	static void Collision_MonsterBullet(list<CGameObject*> _Dst, list<CGameObject*> _Src);
	
	static void Collision_Helicop(list<CGameObject*> _Dst, list<CGameObject*> _Src);
	static void Collision_NPC(list<CGameObject*> _Dst, list<CGameObject*> _Src);
	static void Collision_RectEx(list<CGameObject*> _Dst, list<CGameObject*> _Src);
	static bool Check_Rect(CGameObject* pDst, CGameObject* pSrc, float* _pX, float* _pY);



	static void Collision_Sphere(list<CGameObject*> _Dst, list<CGameObject*> _Src);
	static bool Check_Sphere(CGameObject* pDst, CGameObject* pSrc);
	static void Collision_SLUG(list<CGameObject*> _Dst, list<CGameObject*> _Src);
	static void Collision_BODY(list<CGameObject*> _Dst, list<CGameObject*> _Src);
};

