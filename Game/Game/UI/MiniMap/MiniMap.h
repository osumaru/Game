#pragma once

class MiniMap : public GameObject
{
public:
	void Init();

	void Update();

	void Draw();

private:
	Sprite m_miniMap;
	Texture m_miniMapTexture;

	Sprite m_playerIcon;
	Texture m_playerIconTexture;
};
