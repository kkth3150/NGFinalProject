#include "pch.h"
#include "Enemy_1.h"
#include "Bmp_Manager.h"
#include "Object_Manager.h"
#include "AbstractFactory.h"
#include "Enemy_Bullet.h"
#include "Explosion_Object.h"

CEnemy_1::CEnemy_1()
{
}

CEnemy_1::~CEnemy_1()
{
	Release();
}

void CEnemy_1::Initialize()
{
	CBmp_Manager::Get_Instance()->Insert_Bmp(L"../Image/Enemy/Enemy_1(57X64X11ea).bmp", L"ENEMY_1_IMAGE");
	CBmp_Manager::Get_Instance()->Insert_Bmp(L"../Image/Bullet/EnemyBullet/Enemy_Bullet_1.bmp", L"E1_IMAGE");
	CBmp_Manager::Get_Instance()->Insert_Bmp(L"../Image/Bullet/EnemyBullet/Enemy_Bullet_2.bmp", L"E2_IMAGE");

	m_pFrameKey = L"ENEMY_1_IMAGE";
	m_tInfo.fCX = 57.f;
	m_tInfo.fCY = 64.f;
	m_fSpeed = 2.f;
	m_fSpeed_Y = -2.f;
	m_iFrameCnt = 5;
	m_dwShotCount = GetTickCount64();
	m_dwShotDelay = 1500;
	m_iHp = 10;

}

int CEnemy_1::Update()
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
	m_iFrameCnt = (m_iFrameCnt + 1) % 11;
	if (GetTickCount64() - m_dwShotCount > m_dwShotDelay) {
		Shot();
		m_dwShotCount = GetTickCount64();

	}
	__super::Update_Rect();


	if (m_iHp < 0) {
		m_bDead = true;
		CObject_Manager::Get_Instance()->Add_Object(OBJ_EXPLOSION, CAbstractFactory<CExplosion_Object>::Create(m_tInfo.fX, m_tInfo.fY));
	}

	if (m_bDead)
		return OBJ_DEAD;



	return OBJ_NOEVENT;
}

void CEnemy_1::Late_Update()
{

	if (m_bDead) {
		CObject_Manager::Get_Instance()->Add_Object(OBJ_EXPLOSION, CAbstractFactory<CExplosion_Object>::Create(m_tInfo.fX,m_tInfo.fY));
	}
	__super::Move_Frame();
}

void CEnemy_1::Render(HDC hDC)
{
	HDC EnemyDC = CBmp_Manager::Get_Instance()->Find_Img(m_pFrameKey);

	//Rectangle(hDC, m_tInfo.fX - m_tInfo.fCX / 2, m_tInfo.fY - m_tInfo.fCY / 2, m_tInfo.fX + m_tInfo.fCX / 2, m_tInfo.fY + m_tInfo.fCY / 2);
	//피격 범위용 Rect => 조절 필요

	GdiTransparentBlt(hDC,
		(int)m_tInfo.fX - m_tInfo.fCX / 2,	//복사 받을 X 위치
		(int)m_tInfo.fY - m_tInfo.fCY / 2,	//복사 받을 Y 위치
		57,									//복사 받을 가로 길이
		64,									//복사 받을 세로 길이
		EnemyDC,							//복사할 비트맵 DC
		57 * m_iFrameCnt,					//비트맵 이미지의 왼쪽 X 좌표
		0,									//비트맵 이미지의 위쪽 Y 좌표
		m_tInfo.fCX,						//복사할 이미지의 가로 사이즈
		m_tInfo.fCY,						//복사할 이미지의 세로 사이즈
		RGB(255, 255, 255));

}

void CEnemy_1::Release(void)
{
}


void CEnemy_1::Shot()
{
	CObject_Manager::Get_Instance()->Add_Object(OBJ_BULLET_ENEMY, CAbstractFactory<CEnemy_Bullet>::CreateEnemyBullet(m_tInfo.fX, m_tInfo.fY - 30.f, E1));
	
}

void CEnemy_1::Motion_Change()
{

}
