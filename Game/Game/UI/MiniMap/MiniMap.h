#pragma once

class CMiniMap : public IGameObject
{
public:
	void Init();

	void Update();

	void Draw();

private:
	CSprite m_miniMap;
	CTexture m_miniMapTexture;

	CSprite m_playerIcon;
	CTexture m_playerIconTexture;
};
