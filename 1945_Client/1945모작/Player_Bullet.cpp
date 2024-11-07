#include "pch.h"
#include "Player_Bullet.h"
#include "Bmp_Manager.h"


CPlayer_Bullet::CPlayer_Bullet()
{
	
}

CPlayer_Bullet::~CPlayer_Bullet()
{
}

void CPlayer_Bullet::Initialize()
{

	m_fSpeed = 15.f;
	Motion_Change();
	switch (m_eBulletKind) {
	case PB_NORMAL:
		m_tInfo.fCX = 24.f;
		m_tInfo.fCY = 72.f;
		m_pFrameKey = L"MAINBULLET_IMAGE";

		break;

	case PB_LSUB:
		m_tInfo.fCX = 24.f;
		m_tInfo.fCY = 63.f;
		m_pFrameKey = L"SUBBULLET_IMAGE";
		break;

	case PB_RSUB:
		m_tInfo.fCX = 24.f;
		m_tInfo.fCY = 63.f;
		m_pFrameKey = L"SUBBULLET_IMAGE";
		break;


	case PB_LSIDE:
		m_tInfo.fCX = 24.f;
		m_tInfo.fCY = 42.f;
		m_pFrameKey = L"SIDELBULLET_IMAGE";
		break;

	case PB_RSIDE:
		m_tInfo.fCX = 24.f;
		m_tInfo.fCY = 42.f;
		m_pFrameKey = L"SIDERBULLET_IMAGE";
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
	__super::Move_Frame();

}

void CPlayer_Bullet::Render(HDC hDC)
{
	//Rectangle(hDC, m_tInfo.fX - m_tInfo.fCX / 2, m_tInfo.fY - m_tInfo.fCY / 2, m_tInfo.fX + m_tInfo.fCX / 2, m_tInfo.fY + m_tInfo.fCY / 2);
	HDC	BULLETDC = CBmp_Manager::Get_Instance()->Find_Img(m_pFrameKey);

	GdiTransparentBlt(
		hDC,
		(int)m_tInfo.fX - m_tInfo.fCX / 2,					// 복사받을 Y위치
		(int)m_tInfo.fY - m_tInfo.fCY / 2, 
		(int)m_tInfo.fCX,									// 복사 받을 가로 길이
		(int)m_tInfo.fCY,									// 복사 받을 세로 길이
		BULLETDC,											// 복사할 비트맵 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,			// 비트맵 출력 X좌표
		0,													// 비트맵 출력 Y좌표
		(int)m_tInfo.fCX,									// 복사할 비트맵의 가로 길이
		(int)m_tInfo.fCY,									// 복사할 비트맵의 세로 길이
		RGB(255, 255, 255));

}

void CPlayer_Bullet::Release(void)
{
}

void CPlayer_Bullet::Motion_Change()
{
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount64();
}
