#include "pch.h"
#include "Boss_Bullet.h"

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

	}
	else {
		m_tInfo.fCX = 10.f;
		m_tInfo.fCY = 10.f;
		m_fSpeed = 5.f;
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
}

void CBoss_Bullet::Release(void)
{
}

void CBoss_Bullet::Set_Direction(float x, float y)
{
	m_vDirection = Vector2(x, y).normalize();
}
