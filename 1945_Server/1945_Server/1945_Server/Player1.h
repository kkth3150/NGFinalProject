#pragma once
#include "GameObject.h"
class CPlayer1 : public CGameObject
{
public:

	CPlayer1();
	virtual ~CPlayer1();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Release(void) override;

	void Shot();

	void SetLife();

	void PlayerUP();
	void PlayerDOWN();
	void PlayerLEFT();
	void PlayerRIGHT();

private:

	DWORD					m_dwShotDelay;
	DWORD					m_dwShotCount;


	int						m_iLife;
	int						m_iScore;

	bool					m_bNODie;
};

