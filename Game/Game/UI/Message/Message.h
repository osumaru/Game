#pragma once

class CMessage : public IGameObject
{
public:
	void Init(CVector2 size, wchar_t* string);

	void Update() override;

	void AfterDraw() override;
private:
	CSprite m_window;
	CFont	m_font;
};