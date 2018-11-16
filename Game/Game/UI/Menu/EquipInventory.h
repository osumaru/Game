/*
*	�����C���x���g���N���X
*/

#pragma once

class CMenu;
class IItem;

#include "../../Player/Weapon.h"

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
	void AfterDraw() override;

	//�������X�g�̃e�N�X�`���𐮗�����
	//isInit	�e�N�X�`�������������邩
	void EquipListReset(bool isInit);

	//�J�[�\���ړ�
	void PointerMove();

	//��������
	void Equip();

	//�X�e�[�^�X�v�Z
	void CalucStatus();

	//��������������擾
	static int GetEquipLimit()
	{
		return m_equipLimit;
	}

private:
	//�X�e�[�^�X�̐�
	enum EnStatusNum {
		enStatus_Hp,
		enStatus_Attack,
		enStatus_Defense,
		enStatus_Num
	};
	//�X�e�[�^�X��r�p�̃t�H���g�̐�
	enum EnFontNum {
		enFont_CurrentStatus,
		enFont_ChangeStatus,
		enFont_StatusNum
	};

	static const int					m_equipLimit = 15;								//�����������
	CMenu*								m_menu = nullptr;
	CFont								m_statusFont[enFont_StatusNum][enStatus_Num];	//���݂̑����Ƒ����ύX���̃X�e�[�^�X�\��
	CSprite								m_backGround;									//�w�i
	CTexture							m_backGroundTexture;
	CSprite								m_statusWindow;									//�X�e�[�^�X�E�B���h�E
	CTexture							m_statusWindowTexture;							
	CSprite								m_right;										//�E���
	CTexture							m_rightTexture;
	CSprite								m_pointer;										//�J�[�\��
	CTexture							m_pointerTexture;
	CSprite								m_equip[m_equipLimit];							//�����A�C�R��
	std::list<CWeapon::SWeaponStatus>	m_equipList;									//�������X�g
	std::list<IItem*>					m_itemEquipList;
	CVector2							m_basePos = CVector2::Zero;						//�������W
	CVector2							m_baseSize = CVector2::Zero;					//�����T�C�Y
	int									m_width = 0;									//�C���x���g���̕�
	int									m_height = 0;									//�C���x���g���̍���
	int									m_pointerNum = 0;								//�J�[�\���őI��ł���A�C�e���̔ԍ�
};