#pragma once
#include "GameObject.h"

class CFinger : public CGameObject
{
public:
	CFinger();
	virtual ~CFinger();

public:


	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void SetPlayerID(PLAYERID eID) {
		m_ePlayerID = eID;
	};

	void SetFlight(int flightID) {
		m_iFlight = flightID;
	}

private:
	PLAYERID	m_ePlayerID;
	int			m_iFlight;
};

