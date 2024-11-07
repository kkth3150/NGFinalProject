#include "pch.h"
#include "Boss.h"
#include "Bmp_Manager.h"
#include "Object_Manager.h"
#include "Key_Manager.h"
#include "AbstractFactory.h"

CBoss::CBoss()
{
}

CBoss::~CBoss()
{
}

void CBoss::Initialize()
{
	CBmp_Manager::Get_Instance()->Insert_Bmp(L"../Image/Boss/BossNormal.bmp", L"BOSS_IDLE");
	CBmp_Manager::Get_Instance()->Insert_Bmp(L"../Image/Boss/BossEnd.bmp", L"BOSS_DEAD");
	
	Set_Init_Boss_Parts();

	m_pFrameKey = L"BOSS_IDLE";
	m_tInfo.fX = 1500.f;
	m_tInfo.fY = 150.f;
	m_tInfo.fCX = 1365.f;
	m_tInfo.fCY = 166.f;
	m_fSpeed = 3.f;
	Boss_Page = PAGE_1;
}

int CBoss::Update()
{

	switch (Boss_Page) {
	case PAGE_1:
		if (m_tInfo.fX > 600) {
			m_tInfo.fX -= m_fSpeed;
		}

		break;
	case PAGE_2:

		if (m_tInfo.fX > 0) {
			m_tInfo.fX -= m_fSpeed;
		}

		break;

	case PAGE_3:
		break;

	default:
		break;
	}



	__super::Update_Rect();


	return OBJ_NOEVENT;
}

void CBoss::Late_Update()
{

	switch (Boss_Page) {
	case PAGE_1:

		if (CKey_Manager::Get_Instance()->Key_Down(VK_RETURN))
			Boss_Page = PAGE_2;

		if (CObject_Manager::Get_Instance()->Get_List(OBJ_BOSSPART)->size() < 10)
			Boss_Page = PAGE_2;

		break;

	case PAGE_2:

		if (CObject_Manager::Get_Instance()->Get_List(OBJ_BOSSPART)->size() < 0)
			Boss_Page = PAGE_3;

		break;

	case PAGE_3:
		//폭발 이펙트
		break;

	default:
		break;
	}

	__super::Move_Frame();
}

void CBoss::Render(HDC hDC)
{
	HDC PlayerDC = CBmp_Manager::Get_Instance()->Find_Img(m_pFrameKey);

	//Rectangle(hDC, m_tInfo.fX - m_tInfo.fCX / 2, m_tInfo.fY - m_tInfo.fCY / 2, m_tInfo.fX + m_tInfo.fCX / 2, m_tInfo.fY + m_tInfo.fCY / 2);
	//피격 범위용 Rect => 조절 필요

	GdiTransparentBlt(hDC,
		(int)m_tInfo.fX - m_tInfo.fCX / 2,	//복사 받을 X 위치
		(int)m_tInfo.fY - m_tInfo.fCY / 2,	//복사 받을 Y 위치
		1365,								//복사 받을 가로 길이
		166,								//복사 받을 세로 길이
		PlayerDC,							//복사할 비트맵 DC
		0,									//비트맵 이미지의 왼쪽 X 좌표
		0,									//비트맵 이미지의 위쪽 Y 좌표
		m_tInfo.fCX,						//복사할 이미지의 가로 사이즈 
		m_tInfo.fCY,						//복사할 이미지의 세로 사이즈
		RGB(255, 255, 255));
}

void CBoss::Release(void)
{
}

void CBoss::Set_Init_Boss_Parts()
{

	CObject_Manager::Get_Instance()->Add_Object(OBJ_BOSSPART, CAbstractFactory<CBoss_Posin>::CreatePosin(0));
	CObject_Manager::Get_Instance()->Add_Object(OBJ_BOSSPART, CAbstractFactory<CBoss_Posin>::CreatePosin(1));
	CObject_Manager::Get_Instance()->Add_Object(OBJ_BOSSPART, CAbstractFactory<CBoss_Posin>::CreatePosin(2));
	CObject_Manager::Get_Instance()->Add_Object(OBJ_BOSSPART, CAbstractFactory<CBoss_Posin>::CreatePosin(3));
	CObject_Manager::Get_Instance()->Add_Object(OBJ_BOSSPART, CAbstractFactory<CBoss_Posin>::CreatePosin(4));
	CObject_Manager::Get_Instance()->Add_Object(OBJ_BOSSPART, CAbstractFactory<CBoss_Posin>::CreatePosin(5));
	CObject_Manager::Get_Instance()->Add_Object(OBJ_BOSSPART, CAbstractFactory<CBoss_Posin>::CreatePosin(6));

	CObject_Manager::Get_Instance()->Add_Object(OBJ_BOSSPART, CAbstractFactory<CBoss_Gun>::CreateGun(0));
	CObject_Manager::Get_Instance()->Add_Object(OBJ_BOSSPART, CAbstractFactory<CBoss_Gun>::CreateGun(1));
	CObject_Manager::Get_Instance()->Add_Object(OBJ_BOSSPART, CAbstractFactory<CBoss_Gun>::CreateGun(2));
	CObject_Manager::Get_Instance()->Add_Object(OBJ_BOSSPART, CAbstractFactory<CBoss_Gun>::CreateGun(3));
	CObject_Manager::Get_Instance()->Add_Object(OBJ_BOSSPART, CAbstractFactory<CBoss_Gun>::CreateGun(4));
	CObject_Manager::Get_Instance()->Add_Object(OBJ_BOSSPART, CAbstractFactory<CBoss_Gun>::CreateGun(5));
	CObject_Manager::Get_Instance()->Add_Object(OBJ_BOSSPART, CAbstractFactory<CBoss_Gun>::CreateGun(6));
	CObject_Manager::Get_Instance()->Add_Object(OBJ_BOSSPART, CAbstractFactory<CBoss_Gun>::CreateGun(7));
	CObject_Manager::Get_Instance()->Add_Object(OBJ_BOSSPART, CAbstractFactory<CBoss_Gun>::CreateGun(8));
	CObject_Manager::Get_Instance()->Add_Object(OBJ_BOSSPART, CAbstractFactory<CBoss_Gun>::CreateGun(9));
	CObject_Manager::Get_Instance()->Add_Object(OBJ_BOSSPART, CAbstractFactory<CBoss_Gun>::CreateGun(10));
	CObject_Manager::Get_Instance()->Add_Object(OBJ_BOSSPART, CAbstractFactory<CBoss_Gun>::CreateGun(11));
}
