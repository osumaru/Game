#pragma once

class CArrowRemain : public IGameObject
{
public:
	void Init();

	void Update()override;

	void PostAfterDraw()override;
private:
	static const int DIGIT_NUM = 2;
	static const int DECIMAL_NUM = 10;
	CSprite m_arrowSynbol;
	CSprite m_remainNum[DIGIT_NUM];
	CTexture* m_pNumTexture[DECIMAL_NUM];
};