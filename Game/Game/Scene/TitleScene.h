/*
*	�^�C�g���V�[���N���X
*/
#pragma once
class CTitleScene :public IGameObject
{
public:
	//������
	void Init();

	//�X�V
	void Update() override;

	//�x���`��
	void AfterDraw() override;

private:
	CSprite			m_title;					//Title��ʂ̃X�v���C�g
	CTexture		m_titleTexture;				//Title��ʂ̃e�N�X�`��
};

