#pragma once
class CFade : public IGameObject
{
public:
	CFade();
	~CFade();
	bool Start();
	void Update();
	void AfterDraw();
	void FadeOut(); //�t�F�C�h�A�E�g���s�����߂ɂ��Ăяo�����߂̊֐�
	void FadeIn();	//�t�F�C�h�C�����s�����߂ɌĂяo�����֐�
	//���s�����ǂ�����Ԃ�
	bool IsExecute()
	{
		return m_isExecute;
	}

private:
	enum EnFadeState
	{
		enFadeOut,
		enFadeIn,
	};

	CSprite			m_fadeSprite;							//�X�v���C�g
	CTexture		m_fadeTexture;							//�e�N�X�`��
	float			m_texturerAlpha = 0.0f;
	CVector2		m_texturePosition = { 0.0f,0.0f };
	CVector2		m_textureSize = { 1280,720 };

	float			m_fadeTime = 0.0f;
	bool            m_isExecute = false;					//���s�����ǂ���
	EnFadeState		m_fadeState = enFadeOut;
	const float		FADE_OUT_TIME = 2.0f;					//�t�F�C�h�A�E�g����܂ł̎���
	const float		FADE_IN_TIME = 2.0f;					//�t�F�C�h�C������܂ł̎���

};

