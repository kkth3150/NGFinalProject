#pragma once
#include "GameObject.h"

class CEnemy_Bullet : public CGameObject
{

public:
	CEnemy_Bullet();
	virtual ~CEnemy_Bullet();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void	Motion_Change();

public:

	void Set_BulletKind(ENEMY_BULLET eBullet) { m_eBulletKind = eBullet; };


private:
	const TCHAR* m_pFrameKey;

	float					m_fMIN_X = 30.f;
	float					m_fMIN_Y = 30.f;

	float					m_fMAX_X = 580.f;
	float					m_fMAX_Y = 850.f;

	int						m_iMoveRange;
	int						m_iFrameCnt;
	ENEMY_BULLET			m_eBulletKind;
};

