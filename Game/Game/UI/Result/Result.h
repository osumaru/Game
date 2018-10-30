#pragma once
class CResult: public IGameObject
{
public:
	CResult();
	~CResult();
	void Init();
	void Update();
	void Draw();
	void AfterDraw();

private:
	CSprite			m_result;						//Result��ʂ̃X�v���C�g
	CTexture		m_resultTexture;				//Result��ʂ̃e�N�X�`��
	float			m_alphaTime = 0.0f;
};

