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
	virtual void Release(void) override;

	PLAYERID	m_ePlayerID;
	int			m_iFlight;
};

