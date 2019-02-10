#pragma once

class CMessage : public IGameObject
{
public:
	//������
	//windowSize	�E�B���h�E�T�C�Y
	//textureName	�e�N�X�`���̖��O
	void Init(CVector2 windowSize, wchar_t* textureName);

	//�X�V
	void Update() override;

	//�`��
	void PostAfterDraw() override;

	//��������s�����ɂ��鑬�x��ݒ�
	//alphaSpeed	��������s�����ɂ��鑬�x
	void SetAlphaSpeed(float alphaSpeed)
	{
		m_alphaSpeed = alphaSpeed;
	}

private:
	CSprite		m_window;				//�E�B���h�E
	CSprite		m_message;				//���b�Z�[�W
	float		m_timer = 0.0f;			//�^�C�}�[
	float		m_alphaSpeed = 1.0f;	//��������s�����ɂ��鑬�x
};