#pragma once
#include "Level.h"

class CLevel_GameOver : public CLevel
{
public:
	CLevel_GameOver();
	virtual ~CLevel_GameOver();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

};
