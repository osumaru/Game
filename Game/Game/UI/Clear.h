#pragma once

class CClear : public IGameObject
{
public:
	void Init();

	void Update()override;

	void PostAfterDraw()override;

private:
	CSprite	m_sprite;
	float m_alpha = 0.0f;
};