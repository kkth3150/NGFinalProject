#include "pch.h"
#include "Player.h"
#include "Bmp_Manager.h"
#include "Key_Manager.h"
#include "Object_Manager.h"
#include "AbstractFactory.h"
#include "Player_Bullet.h"
#include "Explosion_Object.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{

	CBmp_Manager::Get_Instance()->Insert_Bmp(L"../Image/Player/FinalPlayer(62X64X7ea).bmp", L"PLAYER_IMAGE");
	CBmp_Manager::Get_Instance()->Insert_Bmp(L"../Image/Bullet/PlayerBullet/MainBullet/MainBullet(24X72X4).bmp", L"MAINBULLET_IMAGE");
	CBmp_Manager::Get_Instance()->Insert_Bmp(L"../Image/Bullet/PlayerBullet/SubBullet/SubBullet(24X63X4).bmp", L"SUBBULLET_IMAGE");
	CBmp_Manager::Get_Instance()->Insert_Bmp(L"../Image/Bullet/PlayerBullet/SideBullet/SideBullet_LEFT(24X42X4).bmp", L"SIDELBULLET_IMAGE");
	CBmp_Manager::Get_Instance()->Insert_Bmp(L"../Image/Bullet/PlayerBullet/SideBullet/SideBullet_RIGHT(24X42X4).bmp", L"SIDERBULLET_IMAGE");

	m_bNODie = false;
	m_dwShotDelay = 100;
	m_pFrameKey = L"PLAYER_IMAGE";
	m_tInfo.fX = 300.f;
	m_tInfo.fY = 800.f;
	m_tInfo.fCX = 62.f;
	m_tInfo.fCY = 64.f;
	m_fSpeed = 3.f;
	m_iFrameCnt = 3;
	m_dwShotCount = GetTickCount64();
	m_dwShotDelay = 150;
	m_ePlayerShotState = PLAYER_FINAL;
	m_iLife = 4;

}

int CPlayer::Update()
{
	++m_iScore;
	Key_Input();
	__super::Update_Rect();


	if (m_bDead) {
		CObject_Manager::Get_Instance()->Add_Object(OBJ_EXPLOSION, CAbstractFactory<CExplosion_Object>::Create(m_tInfo.fX, m_tInfo.fY));
		return OBJ_DEAD;
	}
	return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{
	__super::Move_Frame();
}

void CPlayer::Render(HDC hDC)
{
	HDC PlayerDC = CBmp_Manager::Get_Instance()->Find_Img(m_pFrameKey);

	//Rectangle(hDC, m_tInfo.fX - m_tInfo.fCX / 2, m_tInfo.fY - m_tInfo.fCY / 2, m_tInfo.fX + m_tInfo.fCX / 2, m_tInfo.fY + m_tInfo.fCY / 2);
	//피격 범위용 Rect => 조절 필요

	GdiTransparentBlt(hDC,
		(int)m_tInfo.fX - m_tInfo.fCX / 2,	//복사 받을 X 위치
		(int)m_tInfo.fY - m_tInfo.fCY / 2,	//복사 받을 Y 위치
		62,									//복사 받을 가로 길이
		64,									//복사 받을 세로 길이
		PlayerDC,							//복사할 비트맵 DC
		62 * m_iFrameCnt,					//비트맵 이미지의 왼쪽 X 좌표
		0,									//비트맵 이미지의 위쪽 Y 좌표
		m_tInfo.fCX,						//복사할 이미지의 가로 사이즈 
		m_tInfo.fCY,						//복사할 이미지의 세로 사이즈
		RGB(255, 255, 255));

}

void CPlayer::Release(void)
{

}

void CPlayer::Key_Input()
{
	if (CKey_Manager::Get_Instance()->Key_Pressing(VK_LEFT)) {
		if (m_tInfo.fX > 0.f + m_tInfo.fCX / 2.f) {
			m_tInfo.fX -= m_fSpeed;
			m_eDir = DIR_LEFT;
			if (m_iFrameCnt > 0)
				m_iFrameCnt--;
		}
	}
	else if (CKey_Manager::Get_Instance()->Key_Pressing(VK_RIGHT)) {
		if (m_tInfo.fX < WINCX - m_tInfo.fCX / 2.f) {
			m_tInfo.fX += m_fSpeed;
			m_eDir = DIR_RIGHT;
			if (m_iFrameCnt < 6)
				m_iFrameCnt++;
		}
	}
	else {
		if (m_iFrameCnt < 3)
			m_iFrameCnt++;
		else if (m_iFrameCnt > 3)
			m_iFrameCnt--;
	}


	if (CKey_Manager::Get_Instance()->Key_Pressing(VK_UP)) {
		if (m_tInfo.fY > 0.f + m_tInfo.fCY / 2.f) {
			m_tInfo.fY -= m_fSpeed;
			m_eDir = DIR_UP;
		}
	}

	if (CKey_Manager::Get_Instance()->Key_Pressing(VK_DOWN)) {
		if (m_tInfo.fY < WINCY - m_tInfo.fCY / 2.f) {
			m_tInfo.fY += m_fSpeed;
			m_eDir = DIR_DOWN;
		
		}
	}

	if (CKey_Manager::Get_Instance()->Key_Down(VK_LCONTROL)) {
		m_bNODie = true;
	}


	if (GetTickCount64() - m_dwShotCount > m_dwShotDelay) {
		Shot();
		m_dwShotCount = GetTickCount64();
		
	}

	

}

void CPlayer::Shot()
{
	CObject_Manager::Get_Instance()->Add_Object(OBJ_PLAYERBULLET,CAbstractFactory<CPlayer_Bullet>::CreatePlayerBullet(m_tInfo.fX,m_tInfo.fY-30.f, PB_NORMAL));
	if (m_ePlayerShotState == PLAYER_UPGRADE) {

		CObject_Manager::Get_Instance()->Add_Object(OBJ_PLAYERBULLET, CAbstractFactory<CPlayer_Bullet>::CreatePlayerBullet(m_tInfo.fX - 10.f, m_tInfo.fY - 20.f, PB_LSUB));
		CObject_Manager::Get_Instance()->Add_Object(OBJ_PLAYERBULLET, CAbstractFactory<CPlayer_Bullet>::CreatePlayerBullet(m_tInfo.fX + 10.f, m_tInfo.fY - 20.f, PB_RSUB));

	}
	if (m_ePlayerShotState == PLAYER_FINAL) {
		CObject_Manager::Get_Instance()->Add_Object(OBJ_PLAYERBULLET, CAbstractFactory<CPlayer_Bullet>::CreatePlayerBullet(m_tInfo.fX - 10.f, m_tInfo.fY - 20.f, PB_LSUB));
		CObject_Manager::Get_Instance()->Add_Object(OBJ_PLAYERBULLET, CAbstractFactory<CPlayer_Bullet>::CreatePlayerBullet(m_tInfo.fX + 10.f, m_tInfo.fY - 20.f, PB_RSUB));
		CObject_Manager::Get_Instance()->Add_Object(OBJ_PLAYERBULLET, CAbstractFactory<CPlayer_Bullet>::CreatePlayerBullet(m_tInfo.fX + 22.f, m_tInfo.fY, PB_RSIDE));
		CObject_Manager::Get_Instance()->Add_Object(OBJ_PLAYERBULLET, CAbstractFactory<CPlayer_Bullet>::CreatePlayerBullet(m_tInfo.fX - 22.f, m_tInfo.fY, PB_LSIDE));
	}

}

void CPlayer::Motion_Change()
{
	
}

void CPlayer::Set_Life()
{

	CObject_Manager::Get_Instance()->Add_Object(OBJ_EXPLOSION, CAbstractFactory<CExplosion_Object>::Create(m_tInfo.fX, m_tInfo.fY));
	if (m_iLife > 0)
		--m_iLife;
	
}
