#pragma once
#include "GameObject.h"
class CPlayer2 : public CGameObject
{
public:

	CPlayer2();
	virtual ~CPlayer2();

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

	void SetFrameKey(int key) {
		m_iFrameKey = key;
	}

	int GetFrameKey() {
		return m_iFrameKey;
	}

private:

	DWORD					m_dwShotDelay;
	DWORD					m_dwShotCount;


	int						m_iLife;
	int						m_iScore;
	int						m_iFrameKey;
	bool					m_bNODie;
};

