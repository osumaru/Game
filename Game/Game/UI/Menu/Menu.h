#pragma once
class CMenu : public IGameObject
{
public:
	CMenu();
	~CMenu();

	void Init();
	void Update();
	void Draw();

private:
	CSprite		m_menu;
	CTexture		m_Texture;
	CSprite		m_number;
	CTexture		m_numberTexture;
	bool		m_Draw = false;

};

