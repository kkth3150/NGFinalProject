#include"pch.h"
#include "Explosion_Object.h"
#include "Bmp_Manager.h"

CExplosion_Object::CExplosion_Object()
{
}

CExplosion_Object::~CExplosion_Object()
{
}

void CExplosion_Object::Initialize()
{
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;
	m_fSpeed = 0.f;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 27;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 50;
	m_tFrame.dwTime = GetTickCount64();
	CBmp_Manager::Get_Instance()->Insert_Bmp(L"../Image/Medium_Explosion(50X50X28ea).bmp", L"EXPLO");
	m_pFrameKey = L"EXPLO";
	m_bDead = false;

}

int CExplosion_Object::Update()
{
	if (m_tFrame.iFrameStart == 26)
		m_bDead = true;

	__super::Update_Rect();

	if (m_bDead)
		return OBJ_DEAD;

	return OBJ_NOEVENT;


}

void CExplosion_Object::Late_Update()
{
	__super::Move_Frame();
}

void CExplosion_Object::Render(HDC hDC)
{
	if (!m_bDead) {
		HDC	ExplosionDC = CBmp_Manager::Get_Instance()->Find_Img(m_pFrameKey);

		GdiTransparentBlt(
			hDC,
			(int)m_tInfo.fX - m_tInfo.fCX / 2,					// 복사받을 Y위치
			(int)m_tInfo.fY - m_tInfo.fCY / 2,
			(int)m_tInfo.fCX,									// 복사 받을 가로 길이
			(int)m_tInfo.fCY,									// 복사 받을 세로 길이
			ExplosionDC,											// 복사할 비트맵 DC
			m_tFrame.iFrameStart * (int)m_tInfo.fCX,			// 비트맵 출력 X좌표
			0,													// 비트맵 출력 Y좌표
			(int)m_tInfo.fCX,									// 복사할 비트맵의 가로 길이
			(int)m_tInfo.fCY,									// 복사할 비트맵의 세로 길이
			RGB(255, 255, 255));


	}
}

void CExplosion_Object::Release(void)
{
}
