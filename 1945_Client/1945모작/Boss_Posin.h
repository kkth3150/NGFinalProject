#pragma once
#include "GameObject.h"

class CBoss_Posin : public CGameObject
{
public:
	enum POSIN_NUM { POSIN_1, POSIN_2, POSIN_3, POSIN_MID_LT,POSIN_MID_LB,POSIN_MID_RB, POSIN_MID_RT,POSIN_END };
	enum PLAYER_LOOK { LOOK_TOP, LOOK_RT, LOOK_RIGHT, LOOK_RB, LOOK_BOTTOM, LOOK_LB, LOOK_LEFT, LOOK_LT, LOOK_END };

public:
	CBoss_Posin();
	virtual ~CBoss_Posin();

public:
	virtual void Initialize()		override;
	virtual int	 Update()			override;
	virtual void Late_Update()		override;
	virtual void Render(HDC hDC)	override;
	virtual void Release(void)		override;

public:
	void Set_PosinAngle();
	void Set_PosinPos(int iNum);
	void Shot_By_Dir();

	float angle = 0.0f;
	
	DWORD m_dwShot_Delay;
	DWORD m_dwTimer;
	
	POSIN_NUM	m_ePosinLabel;
	PLAYER_LOOK m_ePosinLook;

	float	m_fDeltaX;
	float	m_fDeltaY;

	float	m_fBossPosX;
	float	m_fBossPosY;

	float	m_fAngle;
	float	m_fDegree;

	int		m_iImageFrame;

};

