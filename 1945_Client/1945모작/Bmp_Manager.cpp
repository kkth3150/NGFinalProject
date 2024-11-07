#include "pch.h"
#include "Bmp_Manager.h"
#include "MyBmp.h"

CBmp_Manager* CBmp_Manager::m_pInstance = nullptr;

CBmp_Manager::CBmp_Manager()
{
}

CBmp_Manager::~CBmp_Manager()
{
	Release();
}

void CBmp_Manager::Insert_Bmp(const TCHAR* pFilePath, const TCHAR* pImgKey)
{
	auto	iter = find_if(m_mapBit.begin(), m_mapBit.end(), CTagFinder(pImgKey));

	if (iter == m_mapBit.end())
	{
		CMyBmp* pBmp = new CMyBmp;
		pBmp->Load_Bmp(pFilePath);

		m_mapBit.insert({ pImgKey, pBmp });
	}
}

HDC CBmp_Manager::Find_Img(const TCHAR* pImgKey)
{
	auto	iter = find_if(m_mapBit.begin(), m_mapBit.end(), CTagFinder(pImgKey));

	if (iter == m_mapBit.end())
		return nullptr;

	return iter->second->Get_MemDC();
}

void CBmp_Manager::Release(void)
{
	for_each(m_mapBit.begin(), m_mapBit.end(), CDeleteMap());
	m_mapBit.clear();
}
