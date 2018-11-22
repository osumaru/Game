#pragma once
#include "../../Player/Player.h"

class CItemInventory;
class CEquipInventory;

class CMenu : public IGameObject
{
public:
	CMenu();
	~CMenu();

	void Init();
	void Update();

	void BeforeDead()override;

	void AfterDraw();
	//�X�e�[�^�X���v�Z����֐�
	void StatusMath();			
	//�X���C���[�̃X�e�[�^�X�̓��͂��s���֐�
	void PlayerStatusInput();	
	//�L�[�̓��͂ɂ�鏈�����s���֐�
	void KeyInputMenu();
	//�v���C���[�̃X�e�[�^�X���ω������ꍇ�ɍēx���l�����������鏈��
	void StatusConversion();

private:
	enum EnMenuState
	{
		enMiniMap,
		enItems,
		enWeapons,
		enSaveGame,
		enExsitGame,
		enNoneMenu,
		num,
	};

	CSprite				m_menu;					//���j���[��ʂ̃X�v���C�g
	CTexture			m_Texture;				//���j���[��ʂ̃e�N�X�`��

	CSprite				m_selectSprite;						//���j���[��ʂ̉H�y���A�C�R���̃X�v���C�g
	CTexture			m_selectTexture;				//���j���[��ʂ̉H�y���A�C�R���e�N�X�`��
	CVector2			m_selectPosition = CVector2::Zero;
	CVector2			m_selectScale = { 70.0f,70.0f };
	const CVector2		SELECT_TEX_POS = { -270.0f,320.0f };

	const float			UI_POSITION_Y_UP_LIMIT = 320.0f;
	const float			UI_POSITION_Y_DOWN_LIMIT = -280.0f;
	const float			UI_OFFSET_Y = 150.0f;
	static const int	NUMBER_LINE = 7;			//�s�̗v�f��
	static const int	NUMBER_COLUMN = 4;			//��̗v�f��
	CSprite				m_number[NUMBER_LINE][NUMBER_COLUMN];				//�v���C���[�̃X�e�[�^�X�̃X�v���C�g(����)
	CTexture*			m_numberTexture[NUMBER_LINE][NUMBER_COLUMN];		//�v���C���[�̃X�e�[�^�X�̃e�N�X�`��(����)

	CVector2			m_numberPos = { 500.0,220.0f };//CVector2::Zero;
	int					m_PlayerStatus[7];			//�v���C���[�̃X�e�[�^�X���������o�ϐ�
	bool				m_draw = false;				//�`����s�����̔��������ϐ��B
	

	EnMenuState			m_menuState = enNoneMenu;
	int					m_stateNum = 0;

	CItemInventory*		m_itemInventory = nullptr;				//�A�C�e���C���x���g��
	CEquipInventory*	m_equipInventory = nullptr;				//�����C���x���g��
};

