#pragma once
#include "GameObject.h"

class CEnemy_2 : public CGameObject
{
public:

public:
	CEnemy_2();
	virtual ~CEnemy_2();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void	Shot();
	void	Motion_Change();



private:

	DWORD					m_dwShotDelay;
	DWORD					m_dwShotCount;
	const TCHAR*			m_pFrameKey;

	float					m_fMIN_X = 30.f;
	float					m_fMIN_Y = 30.f;

	float					m_fMAX_X = 580.f;
	float					m_fMAX_Y = 850.f;


	//STATE					m_ePreState;
	//STATE					m_eCurState;
	int						m_iFrameCnt;
	int						m_iFrameDelay;
	DWORD					m_iFrameTick;


};

