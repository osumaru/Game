#pragma once
class CMenu : public GameObject
{
public:
	CMenu();
	~CMenu();

	void Init();
	void Update();
	void Draw();

private:
	Sprite		m_menu;
	Texture		m_Texture;
	Sprite		m_number;
	Texture		m_numberTexture;

	bool		m_Draw = false;

};

