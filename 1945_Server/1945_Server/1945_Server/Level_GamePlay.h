#pragma once
#include "Level.h"
#include "Player1.h"
#include "Player2.h"

class CLevel_GamePlay : public CLevel
{
public:
	CLevel_GamePlay();
	virtual ~CLevel_GamePlay();

public:

	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Release(void) override;

private:
	int m_iMap_Update = 0;
	int m_iScore;

	bool m_bBossDead = false;
	bool m_bBossGen = false;

public:
	DWORD                   Enemy_Count;
	DWORD					Timer;
	DWORD					END_Time;

	CPlayer1*				Player_C1;
	CPlayer2*				Player_C2;
};
