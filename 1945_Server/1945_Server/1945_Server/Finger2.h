#pragma once
#include "GameObject.h"
class CFinger2 : public CGameObject
{

public:
	CFinger2();
	virtual ~CFinger2();

public:


	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Release(void) override;

	void SetFlight(int i) {
		m_iFlight = i;
	};
	int GetFlight() {

		return m_iFlight;
	}
private:
	PLAYERID	m_ePlayerID;
	int			m_iFlight;
};

