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
	void AfterDraw() override;
private:
	CSprite m_window;	//�E�B���h�E
	CSprite	m_message;	//���b�Z�[�W
};