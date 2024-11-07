#include "pch.h"
#include "Enemy_Bullet.h"
#include "Bmp_Manager.h"


CEnemy_Bullet::CEnemy_Bullet()
{
}

CEnemy_Bullet::~CEnemy_Bullet()
{
}

void CEnemy_Bullet::Initialize()
{
	m_fSpeed = 10.f;
	Motion_Change();
	switch (m_eBulletKind) {
	case E1:
		m_tInfo.fCX = 16.f;
		m_tInfo.fCY = 48.f;
		m_pFrameKey = L"E1_IMAGE";
		break;

	case E2L:
		m_tInfo.fCX = 16.f;
		m_tInfo.fCY = 48.f;
		m_pFrameKey = L"E2_IMAGE";
		break;

	case E2R:
		m_tInfo.fCX = 16.f;
		m_tInfo.fCY = 48.f;
		m_pFrameKey = L"E2_IMAGE";
		break;
	default:
		break;

	}


}

int CEnemy_Bullet::Update()
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
		m_tInfo.fY += m_fSpeed  * sin(80.f * PI / 180.f);
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

void CEnemy_Bullet::Late_Update()
{
	__super::Move_Frame();

}

void CEnemy_Bullet::Render(HDC hDC)
{
	//Rectangle(hDC, m_tInfo.fX - m_tInfo.fCX / 2, m_tInfo.fY - m_tInfo.fCY / 2, m_tInfo.fX + m_tInfo.fCX / 2, m_tInfo.fY + m_tInfo.fCY / 2);
	HDC	BULLETDC = CBmp_Manager::Get_Instance()->Find_Img(m_pFrameKey);

	GdiTransparentBlt(
		hDC,
		m_tRect.left,										// 복사받을 X위치
		m_tRect.top,										// 복사받을 Y위치
		(int)m_tInfo.fCX,									// 복사 받을 가로 길이
		(int)m_tInfo.fCY,									// 복사 받을 세로 길이
		BULLETDC,											// 복사할 비트맵 DC
		0,													// 비트맵 출력 X좌표
		0,													// 비트맵 출력 Y좌표
		(int)m_tInfo.fCX,									// 복사할 비트맵의 가로 길이
		(int)m_tInfo.fCY,									// 복사할 비트맵의 세로 길이
		RGB(255, 255, 255));

}

void CEnemy_Bullet::Release(void)
{
}

void CEnemy_Bullet::Motion_Change()
{
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount64();
}
