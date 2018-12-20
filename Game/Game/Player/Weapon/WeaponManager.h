#pragma once
#include "IWeapon.h"
#include "WeaponCommon.h"

class CPlayer;
//������Ǘ�����N���X

class CWeaponManager
{
public:

	void Init(CPlayer* player);

	void Update();

	void Draw();

	void AfterDraw();

	//���ݎg���Ă��镐��̎�ނ��擾
	EnPlayerWeapon GetCurrentState() const
	{
		return m_weaponState;
	}

	/*
	����̃X�e�[�^�X���擾
	weaponNum	����̎��
	*/
	SWeaponStatus& GetWeaponStatus(EnPlayerWeapon weaponNum)
	{
		return m_weapons[weaponNum]->GetWeaponStatus();
	}

	/*
	������擾
	weaponNum		����̎��
	*/
	IWeapon* GetWeapon(EnPlayerWeapon weaponNum)
	{
		return m_weapons[weaponNum].get();
	}


	/*
	���ݑ������Ă��镐����擾
	*/
	IWeapon* GetWeapon()
	{
		return m_weapons[m_weaponState].get();
	}

	//�U�����Ă��邩�̃t���O���擾
	bool GetIsAttack()
	{
		return m_isAttack;
	}

	//�U�����Ă��邩�̃t���O��ݒ�
	void SetIsAttack(bool isAttack)
	{
		m_isAttack = isAttack;
	}

	//�����蔻�������Ă��邩�̃t���O���擾�B
	bool GetIsAttackCheck()
	{
		return m_isAttackCheck;
	}

	//�����蔻�������Ă��邩�̃t���O��ݒ�
	void SetIsAttackCheck(bool isAttack)
	{
		m_isAttackCheck = isAttack;
	}

	CWeaponTraceDraw& GetWeaponTraceDraw()
	{
		return m_weaponTrace;
	}

	void SetIsTraceDraw(bool isTraceDraw)
	{
		m_isTraceDraw = isTraceDraw;
	}

private:
	EnPlayerWeapon				m_weaponState = enWeaponSword;				//���ݎg���Ă镐��
	std::list<SWeaponStatus>	m_equipList;								//���������̃��X�g
	std::unique_ptr<IWeapon>	m_weapons[enWeaponNum];						//����
	bool						m_isAttack = false;							//�U�������̃t���O
	bool						m_isAttackCheck = false;					//�����蔻�������Ă��邩�̃t���O
	CWeaponTraceDraw			m_weaponTrace;								//����̋O�Ղ�`�悷�邽�߂̃N���X
	bool						m_isTraceDraw = false;
};