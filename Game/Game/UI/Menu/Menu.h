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
	//�X�e�[�^�X���v�Z����֐�
	void StatusMath();			
	//�X���C���[�̃X�e�[�^�X�̓��͂��s���֐�
	void PlayerStatusInput();	
	//�L�[�̓��͂ɂ�鏈�����s���֐�
	void KeyInputMenu();

private:
	enum EnMenuState
	{
		enMiniMap,
		enItems,
		enWeapons,
		enSaveGame,
		enExsitGame,
		num,
	};

	CSprite			m_menu;					//���j���[��ʂ̃X�v���C�g
	CTexture		m_Texture;				//���j���[��ʂ̃e�N�X�`��

	CSprite			m_menuUI;						//���j���[��ʂ̉H�y���A�C�R���̃X�v���C�g
	CTexture		m_menuUITexture;				//���j���[��ʂ̉H�y���A�C�R���e�N�X�`��
	CVector2		m_menuUIPosition = { -270.0f,320.0f };
	CVector2		m_menuUIScale = { 70.0f,70.0f };
	const float		UI_POSITION_Y_UP_LIMIT = 320.0f;
	const float		UI_POSITION_Y_DOWN_LIMIT = -280.0f;
	const float		UI_OFFSET_Y = 150.0f;

	const short int NUMBER_LINE = 7;			//�s�̗v�f��
	const short int NUMBER_COLUMN = 4;			//��̗v�f��
	CSprite	*		m_number[7][4];				//�v���C���[�̃X�e�[�^�X�̃X�v���C�g(����)
	CTexture*		m_numberTexture[7][4];		//�v���C���[�̃X�e�[�^�X�̃e�N�X�`��(����)

	CVector2		m_numberPos = { 500.0,220.0f };//CVector2::Zero;
	int				m_PlayerStatus[7];			//�v���C���[�̃X�e�[�^�X���������o�ϐ�
	bool			m_Draw = false;				//�`����s�����̔��������ϐ��B

	EnMenuState		m_MenuState = enMiniMap;
	int				m_StateNum = 0;
};

