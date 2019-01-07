/*
*	�^�C�g���V�[���N���X
*/
#pragma once

class Map;
class CGameSound;

class CTitleScene :public IGameObject
{
public:
	//�R���X�g���N�^
	CTitleScene();
	//�f�X�g���N�^
	~CTitleScene();
	//true���Ԃ����܂ŌJ��Ԃ��Ă΂��
	bool Start() override;

	//�X�V
	void Update() override;

	//�x���`��
	void AfterDraw() override;

	//���ʑO�ɌĂт������
	void BeforeDead() override;
private:
	Map*		m_map = nullptr;		//�}�b�v
	CGameSound*	m_gameSound = nullptr;	//�Q�[���T�E���h
	CSprite		m_title;				//�^�C�g��
	CSprite		m_start;				//�X�^�[�g
	float		m_timer = 0.0f;			//�^�C�}�[
	const float ALPHA_TIME = 2.0f;		//�����ɂȂ�܂ł̎���
	bool		m_isNoColor = false;	//�����ɂȂ��Ă��邩
};

