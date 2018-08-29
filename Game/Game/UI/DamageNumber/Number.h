#pragma once

class Number : public GameObject
{
public:
	void Init(Vector2 numPos, Vector2 numSize);

	void Update();

	void Draw();

	void SetNumber(int num);
private:
	Sprite	m_number[10];
	Texture m_numberTexture[10];
	int		m_num = 0;
};