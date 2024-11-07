#pragma once
#include "GameObject.h"

class CPlayer : public CGameObject
{
public:
	enum SHOT_STATE {PLAYER_INIT, PLAYER_UPGRADE,PLAYER_FINAL,PLAYER_END};

public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void	Key_Input();
	void	Shot();
	void	Motion_Change();

	int		Get_Score() { return m_iScore; };
	int		Get_Life() { return m_iLife; };

	void	Set_Life();
	//void	Move_Player_Frame();


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
	SHOT_STATE				m_ePlayerShotState;
	int						m_iFrameCnt;

	int						m_iLife;
	int						m_iScore;

	bool					m_bNODie;

};

