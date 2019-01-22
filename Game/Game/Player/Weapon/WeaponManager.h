#pragma once
#include "IWeapon.h"
#include "WeaponCommon.h"
#include "../../Item/InventoryItem/IInventoryEquip.h"

class CPlayer;
//������Ǘ�����N���X

class CWeaponManager
{
public:

	void Init(CPlayer* player);

	void Update();

	void Draw();

	void AfterDraw();

	void ParticleSetting();

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
		return *m_weaponTrace;
	}

	void SetIsTraceDraw(bool isTraceDraw)
	{
		m_isTraceDraw = isTraceDraw;
	}

	//�������̕�����擾
	//weaponNum		����̎��
	IInventoryEquip* GetEquipWeapon(EnPlayerWeapon weaponNum)
	{
		return m_equipWeapon[weaponNum].get();
	}

	//�������̕�����擾
	IInventoryEquip* GetEquipWeapon()
	{
		return m_equipWeapon[m_weaponState].get();
	}

	/////////�폜���邩��/////////
	//�������镐���ݒ�
	//equipWeapon	�ύX����������
	//weaponNum		����̎��
	void SetEquipWeapon(std::unique_ptr<IInventoryEquip> equipWeapon, EnPlayerWeapon weaponNum)
	{
		m_equipWeapon[weaponNum] = std::move(equipWeapon);
	}

	//�������Ă��镐�����������
	//equipWeapon	�ύX����������
	//weaponNum		����̎��
	void ChangeEquipWeapon(std::unique_ptr<IInventoryEquip> equipWeapon, EnPlayerWeapon weaponNum);

	//���݂̕���U���̉񐔂��擾
	int GetAttackCount()
	{
		return m_attackCount;
	}

	//���݂̕���U���̉񐔂�ݒ�
	//attackCount	���݂̕���U���̉�
	void SetAttackCount(int attackCount)
	{
		m_attackCount = attackCount;
	}

private:
	EnPlayerWeapon				m_weaponState = enWeaponSword;				//���ݎg���Ă镐��
	static std::unique_ptr<IInventoryEquip> m_equipWeapon[enWeaponNum];		//�������̕���
	std::unique_ptr<IWeapon>	m_weapons[enWeaponNum];						//����
	bool						m_isAttack = false;							//�U�������̃t���O
	bool						m_isAttackCheck = false;					//�����蔻�������Ă��邩�̃t���O
	CWeaponTraceDraw			m_weaponTrace[2];								//����̋O�Ղ�`�悷�邽�߂̃N���X
	bool						m_isTraceDraw = false;						//����̋O�Ղ̕`��
	int							m_attackCount = 0;							//���݂̕���U���̉�
	std::list<CParticle*>		m_particleList;
	float						m_particleTimer = 0.0f;
	const float					PARTICLE_TIME = 1.0f;
	bool						m_particleDraw = false;
};