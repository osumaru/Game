#pragma once
#include "../../Player/Player.h"

class CMenu : public IGameObject
{
public:
	CMenu();
	~CMenu();

	void Init();
	void Update();

	void AfterDraw();
	void StatusMath();
	void PlayerStatusInput();

private:
	CSprite			m_menu;					//���j���[��ʂ̃X�v���C�g
	CTexture		m_Texture;				//���j���[��ʂ̃e�N�X�`��
	CSprite	*		m_number[7][4];			//�v���C���[�̃X�e�[�^�X�̃X�v���C�g(����)
	CTexture*		m_numberTexture[7][4];	//�v���C���[�̃X�e�[�^�X�̃e�N�X�`��(����)
	CVector2		m_numberPos = { 500.0,220.0f };//CVector2::Zero;
	int				m_PlayerStatus[7];			//�v���C���[�̃X�e�[�^�X���������o�ϐ�
	bool			m_Draw = false;				//�`����s�����̔��������ϐ��B

};

