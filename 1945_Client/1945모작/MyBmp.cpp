#include "pch.h"
#include "MyBmp.h"

CMyBmp::CMyBmp()
{
}

CMyBmp::~CMyBmp()
{
	Release();
}

void CMyBmp::Load_Bmp(const TCHAR* pFilePath)
{
	HDC		hDC = GetDC(g_hWnd);
	m_hMemDC = CreateCompatibleDC(hDC);

	ReleaseDC(g_hWnd, hDC);

	m_hBitmap = (HBITMAP)LoadImage(NULL,		// 프로그램 인스턴스의 핸들, 이미지는 프로그램에서 얻어오는 것이 아니라 파일로부터 읽어올 것이기 NULL값 세팅
		pFilePath,  // 파일의 경로
		IMAGE_BITMAP, // 어떤 타입을 읽어올지 전달 
		0,	// 이미지의 가로 크기
		0,	// 이미지의 세로 크기
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);  // LR_LOADFROMFILE : 파일에서 이미지를 불러오겠다는 의미, LR_CREATEDIBSECTION : 읽어온 파일을 DIB 형태로 변환

	// SelectObject : GDI 오브젝트를 선택하기 전에 기존에 가지고 있던 오브젝트를 반환
	m_hOldBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
}

void CMyBmp::Release()
{
	SelectObject(m_hMemDC, m_hOldBmp);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
}
