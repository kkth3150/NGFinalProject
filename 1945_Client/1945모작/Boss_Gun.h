#pragma once
#include "GameObject.h"

class CBoss_Gun : public CGameObject
{
public:

public:
	CBoss_Gun();
	virtual ~CBoss_Gun();

public:
	virtual void Initialize()		override;
	virtual int	 Update()			override;
	virtual void Late_Update()		override;
	virtual void Render(HDC hDC)	override;
	virtual void Release(void)		override;

	void Motion_Change();
	void Set_Gun_Index(int iNum) {
		m_iGun_Num = iNum;
	}

	void Shot_By_Dir();

public:

	int m_iGun_Num;
	float m_fBossPosX;
	float m_fBossPosY;

	float angle = 0.0f;
	DWORD m_dwShot_Delay;
	DWORD m_dwTimer;

	

};

