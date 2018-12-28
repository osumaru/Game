/*
*	�Q�[���V�[���N���X
*/
#pragma once
class CClearScene :
	public IGameObject
{
public:
	//�R���X�g���N�^
	CClearScene();
	//�f�X�g���N�^
	~CClearScene();
	//true���Ԃ����܂ŌJ��Ԃ��Ă΂��
	bool Start() override;
	//�X�V
	void Update() override;
	//�x���`��
	void AfterDraw() override;

private:
	CSprite			m_clear;					//Clear��ʂ̃X�v���C�g
	CTexture*		m_clearTexture;				//Clear��ʂ̃e�N�X�`��
};

