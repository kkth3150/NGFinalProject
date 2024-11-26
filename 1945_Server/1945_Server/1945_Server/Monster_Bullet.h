#pragma once
#include "GameObject.h"

class CMonster_Bullet : public CGameObject
{
public:
	CMonster_Bullet();
	virtual ~CMonster_Bullet();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Release(void) override;


public:

	void Set_BulletKind(ENEMY_BULLET eBullet) { m_eBulletKind = eBullet; };


private:
	
	float					m_fMIN_X = 30.f;
	float					m_fMIN_Y = 30.f;

	float					m_fMAX_X = 580.f;
	float					m_fMAX_Y = 850.f;

	int						m_iMoveRange;
	ENEMY_BULLET			m_eBulletKind;
};

