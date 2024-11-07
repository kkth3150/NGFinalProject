#include "pch.h"
#include "Button.h"
#include "Key_Manager.h"
#include "Bmp_Manager.h"

CButton::CButton()
{
}

CButton::~CButton()
{
	Release();
}


void CButton::Initialize()
{
	m_tInfo.fCX = 201.f;
	m_tInfo.fCY = 51.f;
	m_Choice = false;
}

int CButton::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();
	
	return OBJ_NOEVENT;
}

void CButton::Late_Update()
{
	POINT	pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (PtInRect(&m_tRect, pt))
	{
		if (CKey_Manager::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			m_Choice = true;
		}
		m_iDrawID = 0;
	}
	else
		m_iDrawID = 1;
}

void CButton::Render(HDC hDC)
{
	HDC	hMemDC = CBmp_Manager::Get_Instance()->Find_Img(m_pFrameKey);

	GdiTransparentBlt(
		hDC,
		m_tRect.left,
		m_tRect.top,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		m_iDrawID * (int)m_tInfo.fCX,
		0,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));
}

void CButton::Release(void)
{
}
