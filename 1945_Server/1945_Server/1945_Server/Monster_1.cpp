#include "pch.h"
#include "Monster_1.h"
#include "Monster_Bullet.h"
#include "Object_Manager.h"
#include "AbstractFactory.h"

CMonster_1::CMonster_1()
{
}

CMonster_1::~CMonster_1()
{
	Release();
}

void CMonster_1::Initialize()
{
	m_tInfo.fCX = 57.f;
	m_tInfo.fCY = 64.f;
	m_fSpeed = 2.f;
	m_fSpeed_Y = -2.f;
	m_dwShotCount = GetTickCount64();
	m_dwShotDelay = 1500;
	m_iHp = 10;

}

int CMonster_1::Update()
{
	if (m_tInfo.fX > m_fMAX_X) {
		m_fSpeed = -2.f;
		m_fSpeed_Y = -2.f;
	}
	else if (m_tInfo.fX < m_fMIN_X) {
		m_fSpeed = 2.f;
		m_fSpeed_Y = -2.f;
	}

	if (m_tInfo.fY < 0) {
		m_fSpeed_Y = 2.f;
	}
	m_tInfo.fX += m_fSpeed;
	m_tInfo.fY += m_fSpeed_Y;
	if (GetTickCount64() - m_dwShotCount > m_dwShotDelay) {
		Shot();
		m_dwShotCount = GetTickCount64();

	}
	__super::Update_Rect();
	return 0;

	if (m_iHp < 0) {
		m_bDead = true;
		//폭발 오브젝트생성
	}

	if (m_bDead)
		return OBJ_NOEVENT;

}

void CMonster_1::Late_Update()
{

}

void CMonster_1::Release(void)
{
}

void CMonster_1::Shot()
{
	/*CObject_Manager::Get_Instance()->Add_Object(OBJ_BULLET_ENEMY, 
		CAbstractFactory<CMonster_Bullet>::CreateEnemyBullet(m_tInfo.fX, m_tInfo.fY - 30.f, E1));*/
}

void CMonster_1::Motion_Change()
{
}
