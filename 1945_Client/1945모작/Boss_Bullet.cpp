#include "pch.h"
#include "Boss_Bullet.h"
#include "Bmp_Manager.h"

CBoss_Bullet::CBoss_Bullet()
{

}

CBoss_Bullet::~CBoss_Bullet()
{

	

}

void CBoss_Bullet::Initialize()
{
	if (m_eBossBulletKind == BOSS_BULLET_GUN) {

		m_tInfo.fCX = 8.f;
		m_tInfo.fCY = 8.f;
		m_fSpeed = 4.f;
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 1;
		m_tFrame.iMotion = 0;
		m_tFrame.dwSpeed = 100;
		m_tFrame.dwTime = GetTickCount64();
		m_pFrameKey = L"MINI_GUN_BULLET";
	}
	else {
		m_tInfo.fCX = 10.f;
		m_tInfo.fCY = 10.f;
		m_fSpeed = 5.f;
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 1;
		m_tFrame.iMotion = 0;
		m_tFrame.dwSpeed = 100;
		m_tFrame.dwTime = GetTickCount64();
		m_pFrameKey = L"POSIN_BULLET";

	}
}

int CBoss_Bullet::Update()
{
	m_tInfo.fX += m_vDirection.x * m_fSpeed;
	m_tInfo.fY += m_vDirection.y * m_fSpeed;


	if (m_bDead)
		return OBJ_DEAD;



	__super::Update_Rect();

	return OBJ_NOEVENT;


}

void CBoss_Bullet::Late_Update()
{
	__super::Move_Frame();
}

void CBoss_Bullet::Render(HDC hDC)
{
	HDC	BOSSBULLETDC = CBmp_Manager::Get_Instance()->Find_Img(m_pFrameKey);

	GdiTransparentBlt(
		hDC,
		(int)m_tInfo.fX - m_tInfo.fCX / 2,					// 복사받을 Y위치
		(int)m_tInfo.fY - m_tInfo.fCY / 2,
		(int)m_tInfo.fCX,									// 복사 받을 가로 길이
		(int)m_tInfo.fCY,									// 복사 받을 세로 길이
		BOSSBULLETDC,											// 복사할 비트맵 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,			// 비트맵 출력 X좌표
		0,													// 비트맵 출력 Y좌표
		(int)m_tInfo.fCX,									// 복사할 비트맵의 가로 길이
		(int)m_tInfo.fCY,									// 복사할 비트맵의 세로 길이
		RGB(255, 255, 255));
}

void CBoss_Bullet::Release(void)
{
	
}

void CBoss_Bullet::Set_Direction(float x, float y)
{
	m_vDirection = Vector2(x, y).normalize();
}
