#pragma once
#include "GameObject.h"
class CMonster_2 :
    public CGameObject
{
public:
	CMonster_2();
	virtual ~CMonster_2();

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

