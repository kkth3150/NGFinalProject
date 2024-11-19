#pragma once
#include "Level.h"

class CLevel_GameEnd : public CLevel
{
public:
	CLevel_GameEnd();
	virtual ~CLevel_GameEnd();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

};

