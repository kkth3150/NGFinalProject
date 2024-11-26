#include "pch.h"
#include "Boss_Posin.h"
#include "Object_Manager.h"
#include "AbstractFactory.h"
#include "Boss_Bullet.h"

CBoss_Posin::CBoss_Posin()
{

}

CBoss_Posin::~CBoss_Posin()
{

}

void CBoss_Posin::Initialize()
{

	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;
	m_dwShot_Delay = 1000;
	m_iHp = 30;
	m_dwTimer = GetTickCount64();

}

int CBoss_Posin::Update()
{
	m_fBossPosX = CObject_Manager::Get_Instance()->Get_List(OBJ_BOSS)->front()->Get_Info().fX;
	m_fBossPosY = CObject_Manager::Get_Instance()->Get_List(OBJ_BOSS)->front()->Get_Info().fY;
	switch (m_ePosinLabel) {

	case POSIN_1:
		m_tInfo.fX = m_fBossPosX - 361;
		m_tInfo.fY = m_fBossPosY - 5;
		break;

	case POSIN_2:
		m_tInfo.fX = m_fBossPosX - 246;
		m_tInfo.fY = m_fBossPosY - 5;
		break;

	case POSIN_3:
		m_tInfo.fX = m_fBossPosX + 337;
		m_tInfo.fY = m_fBossPosY - 5;
		break;

	case POSIN_MID_LT:
		m_tInfo.fX = m_fBossPosX - 71;
		m_tInfo.fY = m_fBossPosY - 37;
		break;

	case POSIN_MID_LB:
		m_tInfo.fX = m_fBossPosX - 71;
		m_tInfo.fY = m_fBossPosY + 26;
		break;

	case POSIN_MID_RT:
		m_tInfo.fX = m_fBossPosX + 168;
		m_tInfo.fY = m_fBossPosY - 37;
		break;

	case POSIN_MID_RB:
		m_tInfo.fX = m_fBossPosX + 168;
		m_tInfo.fY = m_fBossPosY + 26;
		break;

	default:
		break;
	}

	Set_PosinAngle();
	Shot_By_Dir();
	__super::Update_Rect();

	if (m_iHp < 0) {
		//CObject_Manager::Get_Instance()->Add_Object(OBJ_EXPLOSION, CAbstractFactory<CExplosion_Object>::Create(m_tInfo.fX, m_tInfo.fY));
		m_bDead = true;
	}


	if (m_bDead)
		return OBJ_DEAD;


	return OBJ_NOEVENT;

}

void CBoss_Posin::Late_Update()
{
	if (m_bDead) {
		//CObject_Manager::Get_Instance()->Add_Object(OBJ_BOSS, CAbstractFactory<CExplosion_Object>::Create(m_tInfo.fX, m_tInfo.fY));
	}
}

void CBoss_Posin::Release(void)
{

}

void CBoss_Posin::Set_PosinAngle()
{
	m_fDeltaX = CObject_Manager::Get_Instance()->Get_Player(CLIENT_1)->Get_Info().fX - m_tInfo.fX;
	m_fDeltaY = CObject_Manager::Get_Instance()->Get_Player(CLIENT_1)->Get_Info().fY - m_tInfo.fY;


	m_fAngle = atan2(m_fDeltaY, m_fDeltaX);
	m_fDegree = m_fAngle * 180.f / 3.14f;

	if (m_fDegree < 0) {
		m_fDegree += 360;
	}

	if (m_fDegree >= 337.5f || m_fDegree < 22.5f) {
		m_ePosinLook = LOOK_RIGHT;
	}
	else if (m_fDegree >= 22.5f && m_fDegree < 67.5f) {
		m_ePosinLook = LOOK_RB;
	}
	else if (m_fDegree >= 67.5f && m_fDegree < 112.5f) {
		m_ePosinLook = LOOK_BOTTOM;
	}
	else if (m_fDegree >= 112.5f && m_fDegree < 157.5f) {
		m_ePosinLook = LOOK_LB;

	}
	else if (m_fDegree >= 157.5f && m_fDegree < 202.5f) {
		m_ePosinLook = LOOK_LEFT;

	}
	else if (m_fDegree >= 202.5f && m_fDegree < 247.5f) {
		m_ePosinLook = LOOK_LT;
	}
	else if (m_fDegree >= 247.5f && m_fDegree < 292.5f) {

		m_ePosinLook = LOOK_TOP;
	}
	else if (m_fDegree >= 292.5f && m_fDegree < 337.5f) {

		m_ePosinLook = LOOK_RT;
	}
}

void CBoss_Posin::Set_PosinPos(int iNum)
{

	m_ePosinLabel = (POSIN_NUM)iNum;

}

void CBoss_Posin::Shot_By_Dir()
{

	float PlayerX = CObject_Manager::Get_Instance()->Get_Player(CLIENT_1)->Get_Info().fX;
	float PlayerY = CObject_Manager::Get_Instance()->Get_Player(CLIENT_1)->Get_Info().fY;


	if (m_dwTimer + m_dwShot_Delay < GetTickCount64()) {
		m_dwTimer = GetTickCount64();

		float dirX = PlayerX - m_tInfo.fX;
		float dirY = PlayerY - m_tInfo.fY;
		float length = sqrt(dirX * dirX + dirY * dirY);
		if (length != 0) {
			dirX /= length;
			dirY /= length;
		}
		//CObject_Manager::Get_Instance()->Add_Object(OBJ_BULLET_ENEMY,
		//	CAbstractFactory<CBoss_Bullet>::CreateBossBullet(m_tInfo.fX, m_tInfo.fY, dirX, dirY, 1));
	}
}
