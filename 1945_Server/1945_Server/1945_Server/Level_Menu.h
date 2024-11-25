#pragma once
#include "Level.h"
#include "Finger.h"

class CLevel_Menu : public CLevel
{
public:
	CLevel_Menu();
	virtual ~CLevel_Menu();

public:

	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Release(void) override;

private:
	bool Flag[CLIENT_END] = { false,false };

	CFinger* P1Finger;
	CFinger* P2Finger;
};

