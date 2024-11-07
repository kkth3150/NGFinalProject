#include "pch.h"
#include "Enemy_2.h"
#include "Bmp_Manager.h"
#include "Object_Manager.h"
#include "AbstractFactory.h"
#include "Enemy_Bullet.h"
#include "Explosion_Object.h"

CEnemy_2::CEnemy_2()
{
}

CEnemy_2::~CEnemy_2()
{
	Release();
}

void CEnemy_2::Initialize()
{

	CBmp_Manager::Get_Instance()->Insert_Bmp(L"../Image/Enemy/Enemy_2(240X120X2ea).bmp", L"ENEMY_2_IMAGE");
	CBmp_Manager::Get_Instance()->Insert_Bmp(L"../Image/Bullet/EnemyBullet/MainBullet/Enemy_Bullet_1.bmp", L"E1_IMAGE");
	CBmp_Manager::Get_Instance()->Insert_Bmp(L"../Image/Bullet/EnemyBullet/SubBullet/Enemy_Bullet_2.bmp", L"E2_IMAGE");

	m_pFrameKey = L"ENEMY_2_IMAGE";
	m_tInfo.fCX = 240.f;
	m_tInfo.fCY = 120.f;
	m_fSpeed = 4.f;
	m_fSpeed_Y = 1.f;
	m_dwShotCount = GetTickCount64();
	m_dwShotDelay = 2000;
	m_iFrameCnt = 3;
	m_iFrameDelay = 400;
	m_iHp = 30;
	m_iFrameTick = GetTickCount64();

}

int CEnemy_2::Update()
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
		Shot();
		m_dwShotCount = GetTickCount64();

	}
	if (GetTickCount64() - m_iFrameTick > m_iFrameDelay) {
		m_iFrameCnt = (m_iFrameCnt + 1) % 2;
		m_iFrameTick = GetTickCount64();
	}

	if (m_iHp < 0) {
		m_bDead = true;
		CObject_Manager::Get_Instance()->Add_Object(OBJ_EXPLOSION, CAbstractFactory<CExplosion_Object>::Create(m_tInfo.fX, m_tInfo.fY));
	}

	if (m_bDead)
		return OBJ_DEAD;


	return OBJ_NOEVENT;
}

void CEnemy_2::Late_Update()
{

	if (m_bDead) {
		CObject_Manager::Get_Instance()->Add_Object(OBJ_EXPLOSION, CAbstractFactory<CExplosion_Object>::Create(m_tInfo.fX, m_tInfo.fY));
	}
	__super::Move_Frame();
}

void CEnemy_2::Render(HDC hDC)
{
	HDC Enemy2DC = CBmp_Manager::Get_Instance()->Find_Img(m_pFrameKey);

	//Rectangle(hDC, m_tInfo.fX - m_tInfo.fCX / 2, m_tInfo.fY - m_tInfo.fCY / 2, m_tInfo.fX + m_tInfo.fCX / 2, m_tInfo.fY + m_tInfo.fCY / 2);
	//피격 범위용 Rect => 조절 필요

	GdiTransparentBlt(hDC,
		(int)m_tInfo.fX - m_tInfo.fCX / 2,	//복사 받을 X 위치
		(int)m_tInfo.fY - m_tInfo.fCY / 2,	//복사 받을 Y 위치
		240,								//복사 받을 가로 길이
		120,								//복사 받을 세로 길이
		Enemy2DC,							//복사할 비트맵 DC
		240 * m_iFrameCnt,					//비트맵 이미지의 왼쪽 X 좌표
		0,									//비트맵 이미지의 위쪽 Y 좌표
		m_tInfo.fCX,						//복사할 이미지의 가로 사이즈 
		m_tInfo.fCY,						//복사할 이미지의 세로 사이즈
		RGB(255, 255, 255));

}

void CEnemy_2::Release(void)
{
}


void CEnemy_2::Shot()
{
	CObject_Manager::Get_Instance()->Add_Object(OBJ_BULLET_ENEMY, CAbstractFactory<CEnemy_Bullet>::CreateEnemyBullet(m_tInfo.fX + 10.f, m_tInfo.fY - 30.f, E2R));
	CObject_Manager::Get_Instance()->Add_Object(OBJ_BULLET_ENEMY, CAbstractFactory<CEnemy_Bullet>::CreateEnemyBullet(m_tInfo.fX - 10.f, m_tInfo.fY - 30.f, E2L));
}

void CEnemy_2::Motion_Change()
{

}
