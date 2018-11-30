/*
*	�����C���x���g���N���X
*/

#pragma once

class CMenu;
class IItem;

#include "../../Player/Weapon/WeaponManager.h"

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

	//�A�C�e�����̂Ă�
	void Erase();

	//�����������X�g�ɒǉ�
	//weaponStatus		���X�g�ɒǉ����鑕���̃X�e�[�^�X
	static void AddEquipList(SWeaponStatus& weaponStatus);

	//�������X�g���N���A����
	void ClearEquipList();

private:
	//�X�e�[�^�X�̐�
	enum EnStatusNum {
		enStatus_Hp,		//HP
		enStatus_Attack,	//�U����
		enStatus_Defense,	//�h���
		enStatus_Num		//�X�e�[�^�X�̐�
	};
	//�X�e�[�^�X��r�p�̃t�H���g�̐�
	enum EnFontNum {
		enFont_CurrentStatus,	//���݂̃X�e�[�^�X
		enFont_ChangeStatus,	//�ύX�����X�e�[�^�X
		enFont_StatusNum		//�X�e�[�^�X�̐�
	};

	static const int					m_equipLimit = 15;								//�����������
	CMenu*								m_menu = nullptr;								//���j���[
	CFont								m_statusFont[enFont_StatusNum][enStatus_Num];	//���݂̑����Ƒ����ύX���̃X�e�[�^�X�\��
	CSprite								m_backGround;									//�w�i
	CTexture							m_backGroundTexture;
	CSprite								m_statusWindow[enFont_StatusNum];				//�X�e�[�^�X�E�B���h�E
	CSprite								m_right;										//�E���
	CTexture							m_rightTexture;
	CSprite								m_pointer;										//�J�[�\��
	CTexture							m_pointerTexture;
	CSprite								m_equip[m_equipLimit];							//�����A�C�R��
	CSprite								m_equipWeapon[enWeaponNum];						//��������A�C�R��
	CSprite								m_equipFrame[enWeaponNum];						//��������A�C�R���̘g
	CVector2							m_basePos = CVector2::Zero;						//�������W
	CVector2							m_baseSize = CVector2::Zero;					//�����T�C�Y
	int									m_width = 0;									//�C���x���g���̕�
	int									m_height = 0;									//�C���x���g���̍���
	int									m_pointerNum = 0;								//�J�[�\���őI��ł���A�C�e���̔ԍ�
};