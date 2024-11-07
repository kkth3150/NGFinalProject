#pragma once
#include "GameObject.h"

class CBoss : public CGameObject
{
public:
	enum BOSS_PAGE {PAGE_1,PAGE_2,PAGE_3,PAGE_END};


public:
	CBoss();
	virtual ~CBoss();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void Set_Init_Boss_Parts();
	BOSS_PAGE Boss_Page;
};

