#include "pch.h"
#include "Player2.h"
#include "Object_Manager.h"
#include "AbstractFactory.h"
#include "Player_Bullet.h"


CPlayer2::CPlayer2()
{
}

CPlayer2::~CPlayer2()
{
	Release();
}

void CPlayer2::Initialize()
{
	m_tInfo.fX = 0.f;
	m_tInfo.fY = 0.f;
	m_tInfo.fCX = 62.f;
	m_tInfo.fCY = 64.f;
	m_fSpeed = 3.f;
	m_dwShotCount = GetTickCount64();
	m_dwShotDelay = 150;
	m_iLife = 4;
	m_bDie = false;
}

int CPlayer2::Update()
{
	if (GetTickCount64() - m_dwShotCount > m_dwShotDelay) {
		Shot();
		m_dwShotCount = GetTickCount64();

	}
	__super::Update_Rect();

	if (m_bDead) {
		return OBJ_DEAD;
	}

	return OBJ_NOEVENT;
}

void CPlayer2::Late_Update()
{
}

void CPlayer2::Release(void)
{
}

void CPlayer2::Shot()
{
	CObject_Manager::Get_Instance()->Add_Object(OBJ_PLAYERBULLET, CAbstractFactory<CPlayer_Bullet>::CreatePlayerBullet(m_tInfo.fX, m_tInfo.fY - 30.f, PB_NORMAL));
	//if (m_ePlayerShotState == PLAYER_UPGRADE) {

	//	CObject_Manager::Get_Instance()->Add_Object(OBJ_PLAYERBULLET, CAbstractFactory<CPlayer_Bullet>::CreatePlayerBullet(m_tInfo.fX - 10.f, m_tInfo.fY - 20.f, PB_LSUB));
	//	CObject_Manager::Get_Instance()->Add_Object(OBJ_PLAYERBULLET, CAbstractFactory<CPlayer_Bullet>::CreatePlayerBullet(m_tInfo.fX + 10.f, m_tInfo.fY - 20.f, PB_RSUB));

	//}
	//if (m_ePlayerShotState == PLAYER_FINAL) {
	CObject_Manager::Get_Instance()->Add_Object(OBJ_PLAYERBULLET, CAbstractFactory<CPlayer_Bullet>::CreatePlayerBullet(m_tInfo.fX - 22.f, m_tInfo.fY, PB_LSIDE));
	CObject_Manager::Get_Instance()->Add_Object(OBJ_PLAYERBULLET, CAbstractFactory<CPlayer_Bullet>::CreatePlayerBullet(m_tInfo.fX - 10.f, m_tInfo.fY - 20.f, PB_LSUB));
	CObject_Manager::Get_Instance()->Add_Object(OBJ_PLAYERBULLET, CAbstractFactory<CPlayer_Bullet>::CreatePlayerBullet(m_tInfo.fX + 10.f, m_tInfo.fY - 20.f, PB_RSUB));
	CObject_Manager::Get_Instance()->Add_Object(OBJ_PLAYERBULLET, CAbstractFactory<CPlayer_Bullet>::CreatePlayerBullet(m_tInfo.fX + 22.f, m_tInfo.fY, PB_RSIDE));
}

void CPlayer2::SetLife()
{
}

void CPlayer2::PlayerUP()
{
	if (m_tInfo.fY > 0.f + m_tInfo.fCY / 2.f) {
		m_tInfo.fY -= m_fSpeed;
		m_eDir = DIR_UP;
	}
}

void CPlayer2::PlayerDOWN()
{
	if (m_tInfo.fY < WINCY - m_tInfo.fCY / 2.f) {
		m_tInfo.fY += m_fSpeed;
		m_eDir = DIR_DOWN;
	}
}

void CPlayer2::PlayerLEFT()
{
	if (m_tInfo.fX > 0.f + m_tInfo.fCX / 2.f) {
		m_tInfo.fX -= m_fSpeed;
		m_eDir = DIR_LEFT;
	}
}

void CPlayer2::PlayerRIGHT()
{
	if (m_tInfo.fX < WINCX - m_tInfo.fCX / 2.f) {
		m_tInfo.fX += m_fSpeed;
		m_eDir = DIR_RIGHT;
	}
}
