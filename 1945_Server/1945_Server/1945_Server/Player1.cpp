#include "pch.h"
#include "Player1.h"

CPlayer1::CPlayer1()
{
}

CPlayer1::~CPlayer1()
{
	Release();
}

void CPlayer1::Initialize()
{
	m_tInfo.fX = 0.f;
	m_tInfo.fY = 0.f;
	m_tInfo.fCX = 62.f;
	m_tInfo.fCY = 64.f;
	m_fSpeed = 3.f;
	m_dwShotCount = GetTickCount64();
	m_dwShotDelay = 150;
	m_iLife = 4;
}

int CPlayer1::Update()
{
	__super::Update_Rect();

	if (m_bDead) {
		return OBJ_DEAD;
	}

	return OBJ_NOEVENT;
}

void CPlayer1::Late_Update()
{
}

void CPlayer1::Release(void)
{
}

void CPlayer1::Shot()
{
}

void CPlayer1::SetLife()
{
}

void CPlayer1::PlayerUP()
{

}

void CPlayer1::PlayerDOWN()
{

}

void CPlayer1::PlayerLEFT()
{
	if (m_tInfo.fX > 0.f + m_tInfo.fCX / 2.f) {
		m_tInfo.fX -= m_fSpeed;
		m_eDir = DIR_LEFT;
	}
}

void CPlayer1::PlayerRIGHT()
{
	if (m_tInfo.fX < WINCX - m_tInfo.fCX / 2.f) {
		m_tInfo.fX += m_fSpeed;
		m_eDir = DIR_RIGHT;
	}
}
