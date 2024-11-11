#pragma once
#include "GameObject.h"

class CUI : public CGameObject
{
public:
	CUI();
	virtual ~CUI();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void Set_State(UISTATE eState);
	void Set_ScoreUI(int iScore) {
		m_iScore = iScore;
	}
	void Render_ScoreImage(HDC hDC, HDC hMemDC);
	void Render_LifeImage(HDC hDC, HDC hMemDC);
	inline void Set_Choice(const int& Player) { m_Choice = Player; }


private:
	int			m_iDrawID;
	int			m_iScore;
	int			m_iLife;
	int		m_Choice;

	UISTATE		m_eUIState;
	DWORD		m_dwtime;
};

