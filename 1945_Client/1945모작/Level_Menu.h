#pragma once
#include "Level.h"
class CLevel_Menu : public CLevel
{
public:
	CLevel_Menu();
	virtual ~CLevel_Menu();

public:

	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;


private:

	bool m_bButton_Down;
	bool m_bDoOnce;
};

