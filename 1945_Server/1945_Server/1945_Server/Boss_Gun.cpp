#include "pch.h"
#include "Boss_Gun.h"
//#include "Boss_Bullet.h"
#include "Object_Manager.h"
#include "AbstractFactory.h"

CBoss_Gun::CBoss_Gun()
{
}

CBoss_Gun::~CBoss_Gun()
{
}

void CBoss_Gun::Initialize()
{


	m_tInfo.fCX = 28.f;
	m_tInfo.fCY = 28.f;
	m_iHp = 30;
	m_dwShot_Delay = 200;
	m_dwTimer = GetTickCount64();

}

int CBoss_Gun::Update()
{
	m_fBossPosX = CObject_Manager::Get_Instance()->Get_List(OBJ_BOSS)->front()->Get_Info().fX;
	m_fBossPosY = CObject_Manager::Get_Instance()->Get_List(OBJ_BOSS)->front()->Get_Info().fY;

	switch (m_iGun_Num) {
	case 0:
		m_tInfo.fX = m_fBossPosX - 457.f;
		m_tInfo.fY = m_fBossPosY - 46.f;
		break;

	case 1:
		m_tInfo.fX = m_fBossPosX - 495.f;
		m_tInfo.fY = m_fBossPosY - 18.f;
		break;

	case 2:
		m_tInfo.fX = m_fBossPosX - 495.f;
		m_tInfo.fY = m_fBossPosY + 10.f;
		break;

	case 3:
		m_tInfo.fX = m_fBossPosX - 457.f;
		m_tInfo.fY = m_fBossPosY + 36.f;
		break;

	case 4:
		m_tInfo.fX = m_fBossPosX - 199.f;
		m_tInfo.fY = m_fBossPosY - 58.f;
		break;

	case 5:
		m_tInfo.fX = m_fBossPosX - 199.f;
		m_tInfo.fY = m_fBossPosY + 47.f;
		break;

	case 6:
		m_tInfo.fX = m_fBossPosX + 22.f;
		m_tInfo.fY = m_fBossPosY - 68.f;
		break;

	case 7:
		m_tInfo.fX = m_fBossPosX + 22.f;
		m_tInfo.fY = m_fBossPosY + 57.f;
		break;

	case 8:
		m_tInfo.fX = m_fBossPosX + 75.f;
		m_tInfo.fY = m_fBossPosY - 68.f;
		break;

	case 9:
		m_tInfo.fX = m_fBossPosX + 75.f;
		m_tInfo.fY = m_fBossPosY + 57.f;
		break;

	case 10:
		m_tInfo.fX = m_fBossPosX + 495.f;
		m_tInfo.fY = m_fBossPosY + 50.f;
		break;

	case 11:
		m_tInfo.fX = m_fBossPosX + 495.f;
		m_tInfo.fY = m_fBossPosY - 61.f;
		break;

	default:

		break;
	}


	//Shot_By_Dir();

	__super::Update_Rect();
	if (m_iHp < 0) {
		/*CObject_Manager::Get_Instance()->Add_Object(OBJ_EXPLOSION, CAbstractFactory<CExplosion_Object>::Create(m_tInfo.fX, m_tInfo.fY));*/
		m_bDead = true;
	}


	if (m_bDead)
		return OBJ_DEAD;

	return OBJ_NOEVENT;
}

void CBoss_Gun::Late_Update()
{

	if (m_bDead) {
		//CObject_Manager::Get_Instance()->Add_Object(OBJ_BOSS, CAbstractFactory<CExplosion_Object>::Create(m_tInfo.fX, m_tInfo.fY));
	}
}


void CBoss_Gun::Release(void)
{
}

void CBoss_Gun::Shot_By_Dir()
{

	angle += 10.0f;
	if (angle >= 360.0f) {
		angle -= 360.0f;
	}

	if (m_dwTimer + m_dwShot_Delay < GetTickCount64()) {
		m_dwTimer = GetTickCount64();


		float radians = angle * (3.14159265f / 180.0f);
		float dirX = cos(radians);
		float dirY = sin(radians);

		CObject_Manager::Get_Instance()->Add_Object(OBJ_BULLET_ENEMY,
			CAbstractFactory<CBoss_Bullet>::CreateBossBullet(m_tInfo.fX, m_tInfo.fY, dirX, dirY, 0));
	}
}

