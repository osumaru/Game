#pragma once
class CResult: public IGameObject
{
public:
	CResult();
	~CResult();
	void Init();
	void Update();
	void Draw();
	void PostAfterDraw();

	//�`�悳�ꂽ��
	bool GetDraw()
	{
		return m_isDraw;
	}
private:
	CSprite			m_result;						//Result��ʂ̃X�v���C�g
	CTexture*		m_resultTexture;				//Result��ʂ̃e�N�X�`��
	float			m_alphaTime = 0.0f;
	bool			m_isDraw = false;	//�`�悳�ꂽ��
};

