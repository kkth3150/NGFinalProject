#include "pch.h"
#include "Player_Bullet.h"

CPlayer_Bullet::CPlayer_Bullet()
{
}

CPlayer_Bullet::~CPlayer_Bullet()
{
}

void CPlayer_Bullet::Initialize()
{
	m_fSpeed = 15.f;
	switch (m_eBulletKind) {
	case PB_NORMAL:
		m_tInfo.fCX = 24.f;
		m_tInfo.fCY = 72.f;

		break;

	case PB_LSUB:
		m_tInfo.fCX = 24.f;
		m_tInfo.fCY = 63.f;
		break;

	case PB_RSUB:
		m_tInfo.fCX = 24.f;
		m_tInfo.fCY = 63.f;
		break;


	case PB_LSIDE:
		m_tInfo.fCX = 24.f;
		m_tInfo.fCY = 42.f;
		break;

	case PB_RSIDE:
		m_tInfo.fCX = 24.f;
		m_tInfo.fCY = 42.f;
		break;

	default:
		break;

	}
}

int CPlayer_Bullet::Update()
{
	if (m_iMoveRange > 900) {
		m_bDead = true;
	}

	if (m_bDead)
		return OBJ_DEAD;



	switch (m_eBulletKind) {
	case PB_NORMAL:
		m_tInfo.fY -= m_fSpeed;
		m_iMoveRange += m_fSpeed;
		break;

	case PB_LSUB:
		m_tInfo.fX -= m_fSpeed * cos(88.f * PI / 180.f);
		m_tInfo.fY -= m_fSpeed * sin(88.f * PI / 180.f);
		m_iMoveRange += m_fSpeed;

		break;

	case PB_RSUB:
		m_tInfo.fX += m_fSpeed * cos(88.f * PI / 180.f);
		m_tInfo.fY -= m_fSpeed * sin(88.f * PI / 180.f);
		m_iMoveRange += m_fSpeed;
		break;

	case PB_LSIDE:
		m_tInfo.fX -= m_fSpeed * cos(80.f * PI / 180.f);
		m_tInfo.fY -= m_fSpeed * sin(80.f * PI / 180.f);
		m_iMoveRange += m_fSpeed;
		break;

	case PB_RSIDE:
		m_tInfo.fX += m_fSpeed * cos(80.f * PI / 180.f);
		m_tInfo.fY -= m_fSpeed * sin(80.f * PI / 180.f);
		m_iMoveRange += m_fSpeed;
		break;

	default:
		break;

	}

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer_Bullet::Late_Update()
{

}

void CPlayer_Bullet::Release(void)
{
}
