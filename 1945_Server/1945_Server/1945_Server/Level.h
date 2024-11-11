#pragma once
#include "Define.h"

class CLevel
{
public:
	CLevel();
	virtual ~CLevel();

public:
	virtual void Initialize()PURE;
	virtual int	 Update()PURE;
	virtual void Late_Update()PURE;
	virtual void Release(void)PURE;
};
