#pragma once
#include "IWeapon.h"

class CPlayer;
//������Ǘ�����N���X

class CWeaponManager
{
public:
	enum EnPlayerWeapon
	{
		enSword,			//�Ў茕
		enLongSword,		//���茕
		enArrow,				//�|��
		enTwinSword,		//��
		enWeaponNum,
		enInvalid			//�����Ȃ�
	};

	void Init(CPlayer* player);

	void Update();

	void Draw();

	void AfterDraw();

	EnPlayerWeapon GetCurrentState() const
	{
		return m_weaponState;
	}

	struct SWeaponStatus
	{
		int attack = 0;
		int diffence = 0;
		EnPlayerWeapon weaponNum = enInvalid;
	};

	//�����������X�g�ɒǉ�
	//item		�������X�g�ɒǉ�����A�C�e��
	void AddEquipList(SWeaponStatus& item);

	//�����̕ύX
	//number		�ύX�����������̔ԍ�
	void ChangeEquip(int number);

	//�����������X�g���擾
	std::list<SWeaponStatus>& GetEquipList()
	{
		return m_equipList;
	}

	/*
	����̃X�e�[�^�X���擾
	weaponNum	����̎��
	*/
	SWeaponStatus& GetWeaponStatus(EnPlayerWeapon weaponNum)
	{
		return m_equipWeapon[weaponNum];
	}

	IWeapon* GetWeapon(EnPlayerWeapon weaponNum)
	{
		return m_weapons[weaponNum].get();
	}
	bool GetIsAttack()
	{
		return m_isAttack;
	}

	void SetIsAttack(bool isAttack)
	{
		m_isAttack = isAttack;
	}

	bool GetIsAttackCheck()
	{
		return m_isAttackCheck;
	}

	void SetIsAttackCheck(bool isAttack)
	{
		m_isAttackCheck = isAttack;
	}

private:
	CPlayer*					m_pPlayer = nullptr;						//�v���C���[�̃C���X�^���X
	EnPlayerWeapon				m_weaponState = EnPlayerWeapon::enSword;	//���ݎg���Ă镐��
	std::list<SWeaponStatus>	m_equipList;								//���������̃��X�g
	SWeaponStatus				m_equipWeapon[enWeaponNum];		//�������̕���m�X�e�[�^�X
	std::unique_ptr<IWeapon>	m_weapons[enWeaponNum];
	bool						m_isAttack = false;
	bool						m_isAttackCheck = false;
};