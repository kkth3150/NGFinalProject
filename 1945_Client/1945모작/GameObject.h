#pragma once
#include "Define.h"

class CGameObject
{
public:
	CGameObject();
	virtual ~CGameObject();

public:
	virtual void Initialize()PURE;
	virtual int	 Update()PURE;
	virtual void Late_Update()PURE;
	virtual void Render(HDC hDC)PURE;
	virtual void Release(void)PURE;

public:
	void		Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}
	void		Set_Direction(DIRECTION eDir) { m_eDir = eDir; }
	void		Set_Dead() { m_bDead = true; }
	void		Set_DeadMotion() { m_bDeadMotion = true; }
	void		Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
	void		Set_Size(float fCX, float fCY) { m_tInfo.fCX = fCX, m_tInfo.fCY = fCY; };

	void		Set_Target(CGameObject* _pTarget) { m_pTarget = _pTarget; }

	void		Set_X(float _fX) { m_tInfo.fX += _fX; }
	void		Set_Y(float _fY) { m_tInfo.fY += _fY; }
	void		Set_FrameKey(const TCHAR* pFrameKey) { m_pFrameKey = pFrameKey; }
	void		Set_Frame(int iFrameEnd, DWORD FrameSpeed) {
	
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = iFrameEnd;
		m_tFrame.dwSpeed = FrameSpeed;
		m_tFrame.dwTime = GetTickCount64();
	};
	const RECT* Get_Rect() { return &m_tRect; }
	INFO		Get_Info() { return m_tInfo; }
	bool		Get_Dead() { return m_bDead; }
	int			Get_HP() { return m_iHp; };
	void		Set_Hp(int iAtk) { m_iHp -= iAtk; };
	int			Get_Atk() { return m_iAttack; }

protected:
	void		Update_Rect();
	void		Move_Frame();

protected:
	CGameObject* m_pTarget;
	INFO		m_tInfo;
	RECT		m_tRect;
	DIRECTION	m_eDir;
	FRAME		m_tFrame;

	bool		m_bDead;

	float		m_fSpeed;
	float		m_fAngle;
	int			m_iHp;
	int			m_iAttack;
	float		m_fSpeed_Y;

	bool		m_bDeadMotion;

	const TCHAR* m_pFrameKey;

};

