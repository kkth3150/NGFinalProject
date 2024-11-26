#include "pch.h"
#include "Monster_2.h"
#include "Monster_Bullet.h"
#include "Object_Manager.h"
#include "AbstractFactory.h"

CMonster_2::CMonster_2()
{
}

CMonster_2::~CMonster_2()
{
	Release();
}

void CMonster_2::Initialize()
{
	m_tInfo.fCX = 240.f;
	m_tInfo.fCY = 120.f;
	m_fSpeed = 4.f;
	m_fSpeed_Y = 1.f;
	m_dwShotCount = GetTickCount64();
	m_dwShotDelay = 2000;
	m_iHp = 30;
}

int CMonster_2::Update()
{
	__super::Update_Rect();

	if (m_tInfo.fX > m_fMAX_X) {
		m_fSpeed = -4.f;
	}
	else if (m_tInfo.fX < m_fMIN_X) {
		m_fSpeed = 4.f;
	}
	else if (m_tInfo.fY > 900) {
		m_fSpeed_Y = -1.f;
	}

	m_tInfo.fX += m_fSpeed;
	m_tInfo.fY += m_fSpeed_Y;

	if (GetTickCount64() - m_dwShotCount > m_dwShotDelay) {
		//Shot();
		m_dwShotCount = GetTickCount64();

	}


	if (m_iHp < 0) {
		m_bDead = true;
		//CObject_Manager::Get_Instance()->Add_Object(OBJ_EXPLOSION, CAbstractFactory<CExplosion_Object>::Create(m_tInfo.fX, m_tInfo.fY));
	}

	if (m_bDead)
		return OBJ_DEAD;

	return OBJ_NOEVENT;
}

void CMonster_2::Late_Update()
{

}

void CMonster_2::Release(void)
{
}

void CMonster_2::Shot()
{
	/*CObject_Manager::Get_Instance()->Add_Object(OBJ_BULLET_ENEMY, CAbstractFactory<CMonster_Bullet>::CreateEnemyBullet(m_tInfo.fX + 10.f, m_tInfo.fY - 30.f, E2R));
	CObject_Manager::Get_Instance()->Add_Object(OBJ_BULLET_ENEMY, CAbstractFactory<CMonster_Bullet>::CreateEnemyBullet(m_tInfo.fX - 10.f, m_tInfo.fY - 30.f, E2L));*/
}

void CMonster_2::Motion_Change()
{
}
