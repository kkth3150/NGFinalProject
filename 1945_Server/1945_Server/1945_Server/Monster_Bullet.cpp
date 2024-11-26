#include "pch.h"
#include "Monster_Bullet.h"

CMonster_Bullet::CMonster_Bullet()
{
}

CMonster_Bullet::~CMonster_Bullet()
{
}

void CMonster_Bullet::Initialize()
{
	m_fSpeed = 10.f;
	switch (m_eBulletKind) {
	case E1:
		m_tInfo.fCX = 16.f;
		m_tInfo.fCY = 48.f;
		break;

	case E2L:
		m_tInfo.fCX = 16.f;
		m_tInfo.fCY = 48.f;
		break;

	case E2R:
		m_tInfo.fCX = 16.f;
		m_tInfo.fCY = 48.f;
		break;
	default:
		break;

	}

}

int CMonster_Bullet::Update()
{
	if (m_iMoveRange > 900) {
		m_bDead = true;
	}
	if (m_bDead)
		return OBJ_DEAD;

	switch (m_eBulletKind) {
	case E1:
		m_tInfo.fY += m_fSpeed;
		m_iMoveRange += m_fSpeed;
		break;

	case E2L:
		m_tInfo.fX -= m_fSpeed * cos(80.f * PI / 180.f);
		m_tInfo.fY += m_fSpeed * sin(80.f * PI / 180.f);
		m_iMoveRange += m_fSpeed;

		break;

	case E2R:
		m_tInfo.fX += m_fSpeed * cos(80.f * PI / 180.f);
		m_tInfo.fY += m_fSpeed * sin(80.f * PI / 180.f);
		m_iMoveRange += m_fSpeed;
		break;
	default:
		break;

	}

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster_Bullet::Late_Update()
{
}

void CMonster_Bullet::Release(void)
{
}
