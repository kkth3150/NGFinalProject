#include "pch.h"
#include "Boss.h"
#include "AbstractFactory.h"
#include "Object_Manager.h";
#include "Boss_Gun.h"
#include "Boss_Posin.h"

CBoss::CBoss()
{
}

CBoss::~CBoss()
{
}

void CBoss::Initialize()
{
    Set_Init_Boss_Parts();
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

		if (CObject_Manager::Get_Instance()->Get_List(OBJ_BOSSPART)->size() < 10)
			Boss_Page = PAGE_2;

		break;

	case PAGE_2:

		if (CObject_Manager::Get_Instance()->Get_List(OBJ_BOSSPART)->size() < 0)
			Boss_Page = PAGE_3;

		break;

	case PAGE_3:
		//Æø¹ß ÀÌÆåÆ®
		break;

	default:
		break;
	}
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
