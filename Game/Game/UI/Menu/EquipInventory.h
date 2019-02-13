/*
*	�����C���x���g���N���X
*/

#pragma once

class CMenu;
class IItem;
class IInventoryEquip;
#include "../../Player/Weapon/WeaponCommon.h"
#include "../../Item/EquipList.h"

class CEquipInventory : public IGameObject
{
public:
	//�R���X�g���N�^
	CEquipInventory();

	//�f�X�g���N�^
	~CEquipInventory();

	//������
	//menu		���j���[�̃|�C���^
	void Init(CMenu* menu);

	//�X�V�����O�Ɉ�x�����Ă΂��
	bool Start() override;

	//�X�V
	void Update() override;

	//�`��
	void PostAfterDraw() override;

	//�������X�g�̐�������
	void EquipListReset();

	//�J�[�\���ړ�
	void PointerMove();

	//��������
	void Equip();

	//�X�e�[�^�X�v�Z
	void CalucStatus();

	//�A�C�e�����̂Ă�
	void Erase();

	//�X�e�[�^�X�̐�
	enum EnStatusNum
	{
		enStatus_Hp,		//HP
		enStatus_Attack,	//�U����
		enStatus_Defense,	//�h���
		enStatus_Num		//�X�e�[�^�X�̐�
	};

private:

	//�X�e�[�^�X��r�p�̃t�H���g�̐�
	enum EnFontNum {
		enFont_CurrentStatus,	//���݂̃X�e�[�^�X
		enFont_ChangeStatus,	//�ύX�����X�e�[�^�X
		enFont_StatusNum		//�X�e�[�^�X�̐�
	};
	CMenu*			 m_menu = nullptr;								//���j���[
	CSprite			 m_headline;									//����
	CSprite			 m_background;									//�w�i
	CSprite			 m_inventoryWindow;								//�C���x���g���E�B���h�E
	CSprite			 m_statusWindow[enFont_StatusNum];				//�X�e�[�^�X�E�B���h�E
	CSprite			 m_right;										//�E���
	CSprite			 m_pointer;										//�J�[�\��
	CSprite			 m_frame[CEquipList::m_equipLimit];							//�C���x���g���̘g
	CSprite			 m_equipWeapon[enWeaponNum];					//��������A�C�R��
	CSprite			 m_equipFrame[enWeaponNum];						//��������A�C�R���̘g
	CSprite			 m_buttonBackground;							//�{�^���w�i
	CSprite			 m_buttonA;										//A�{�^��
	CSprite			 m_buttonB;										//B�{�^��
	CSprite			 m_buttonY;										//Y�{�^��
	CSprite			 m_buttonAMoji;									//A�{�^������
	CSprite			 m_buttonBMoji;									//B�{�^������
	CSprite			 m_buttonYMoji;									//Y�{�^������
	CFont			 m_equipName[enFont_StatusNum];					//�����̖��O
	CFont			 m_statusFont[enFont_StatusNum][enStatus_Num];	//���݂̑����Ƒ����ύX���̃X�e�[�^�X����
	CFont			 m_statusFontNum[enFont_StatusNum][enStatus_Num];//���݂̑����Ƒ����ύX���̃X�e�[�^�X���l
	CVector2		 m_basePos = CVector2::Zero;					//�������W
	CVector2		 m_baseSize = CVector2::Zero;					//�����T�C�Y
	int				 m_width = 0;									//�C���x���g���̕�
	int				 m_height = 0;									//�C���x���g���̍���
	int				 m_pointerNum = 0;								//�J�[�\���őI��ł���A�C�e���̔ԍ�
};