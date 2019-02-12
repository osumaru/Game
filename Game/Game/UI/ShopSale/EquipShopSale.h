/*
*	�����C���x���g���N���X
*/

#pragma once

class CMenu;
class IItem;
class IInventoryEquip;
#include "../../Player/Weapon/WeaponCommon.h"
#include "../../Item/EquipList.h"

class CEquipShopSale : public IGameObject
{
public:
	//�R���X�g���N�^
	CEquipShopSale();

	//�f�X�g���N�^
	~CEquipShopSale();

	//������
	void Init();

	//�X�V
	void Update() override;

	//�`��
	void PostAfterDraw() override;

	//�������X�g�̐�������
	void EquipListReset();

	//�J�[�\���ړ�
	void PointerMove();

	//�A�C�e���𔄋p����
	void Sale();

private:
	//�X�e�[�^�X�̐�
	enum EnStatusNum
	{
		enStatus_Hp,		//HP
		enStatus_Attack,	//�U����
		enStatus_Defense,	//�h���
		enStatus_Num		//�X�e�[�^�X�̐�
	};

	CSprite			 m_headline;									//����
	CSprite			 m_background;									//�w�i
	CSprite			 m_inventoryWindow;								//�C���x���g���E�B���h�E
	CSprite			 m_statusWindow;				//�X�e�[�^�X�E�B���h�E
	CSprite			 m_pointer;										//�J�[�\��
	CSprite			 m_frame[CEquipList::m_equipLimit];				//�C���x���g���̘g
	CFont			 m_equipName;									//�����̖��O
	CFont			 m_statusFont[enStatus_Num];					//���݂̑����Ƒ����ύX���̃X�e�[�^�X����
	CFont			 m_statusFontNum[enStatus_Num];					//���݂̑����Ƒ����ύX���̃X�e�[�^�X���l
	CVector2		 m_basePos = CVector2::Zero;					//�������W
	CVector2		 m_baseSize = CVector2::Zero;					//�����T�C�Y
	int				 m_width = 0;									//�C���x���g���̕�
	int				 m_height = 0;									//�C���x���g���̍���
	int				 m_pointerNum = 0;								//�J�[�\���őI��ł���A�C�e���̔ԍ�
	CSoundSource	 m_equipSound[2];
	CFont			m_money;
};