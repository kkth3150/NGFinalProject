#pragma once
#include "Define.h"
class CMyBmp;

class CBmp_Manager
{
private:
	CBmp_Manager();
	~CBmp_Manager();

public:
	void		Insert_Bmp(const TCHAR* pFilePath, const TCHAR* pImgKey);
	HDC			Find_Img(const TCHAR* pImgKey);
	void		Release(void);

public:
	static	CBmp_Manager* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CBmp_Manager;
		}
		return m_pInstance;
	}

	static void			Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static	CBmp_Manager* m_pInstance;

	map<const TCHAR*, CMyBmp*>		m_mapBit;
};

