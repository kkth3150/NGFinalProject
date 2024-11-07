#pragma once
#include "GameObject.h"

class CExplosion_Object : public CGameObject
{
public:
	CExplosion_Object();
	virtual ~CExplosion_Object();
public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;


	const TCHAR* m_pFrameKey;
};

