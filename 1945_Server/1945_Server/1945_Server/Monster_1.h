#pragma once
#include "GameObject.h"
class CMonster_1 :
    public CGameObject
{

public:
	CMonster_1();
	virtual ~CMonster_1();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Release(void) override;

	void	Shot();
	void	Motion_Change();

	DWORD					m_dwShotDelay;
	DWORD					m_dwShotCount;

	float					m_fMIN_X = 30.f;
	float					m_fMIN_Y = 30.f;

	float					m_fMAX_X = 580.f;
	float					m_fMAX_Y = 850.f;

};

