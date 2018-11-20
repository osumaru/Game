#pragma once
class CLoadScene: public IGameObject
{
public:
	CLoadScene();
	~CLoadScene();
	bool Start();
	void Update();
	void AfterDraw();
	void IsDraw(const bool setdraw)
	{
		m_isDraw = setdraw;
	}
private:
	CFont			m_font;
	CVector2		m_fontPosition = CVector2::Zero;
	wchar_t			m_text[256];
	bool			m_isDraw = false;
};

