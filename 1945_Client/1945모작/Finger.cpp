#include "pch.h"
#include "Finger.h"
#include "Bmp_Manager.h"
#include "Object_Manager.h"
#include "Key_Manager.h"
#include "Server_Connection.h"

CFinger::CFinger()
{
}

CFinger::~CFinger()
{
}

void CFinger::Initialize()
{
	m_iFlight = 0;
}

int CFinger::Update()
{

	if (m_iFlight == 0)
		Set_Pos(175 + (int)m_ePlayerID * 60, 150);
	if (m_iFlight == 1)
		Set_Pos(500 + (int)m_ePlayerID * 60, 150);
	if (m_iFlight == 2)
		Set_Pos(350 + (int)m_ePlayerID * 60, 250);
	__super::Update_Rect();

	

	return OBJ_NOEVENT;
}

void CFinger::Late_Update()
{
}

void CFinger::Render(HDC hDC)
{
	HDC	hMemDC = CBmp_Manager::Get_Instance()->Find_Img(m_pFrameKey);
	GdiTransparentBlt(
		hDC,
		m_tRect.left,
		m_tRect.top,
		60,
		60,
		hMemDC,
		(int)m_ePlayerID * m_tInfo.fCX,
		0,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));
}

void CFinger::Release(void)
{
}

void CFinger::MoveRight()
{



	if (m_iFlight < 2) {
		++m_iFlight;
	}
	else {
		m_iFlight = 0;
	}

}

void CFinger::MoveLeft(){

	if (m_iFlight > 0) {
		--m_iFlight;
	}
	else {
		m_iFlight = 2;
	}


}

int CFinger::GetMyFlight()
{
	return m_iFlight;
}

void CFinger::SetMyFlight(int num)
{
	m_iFlight = num;
}
