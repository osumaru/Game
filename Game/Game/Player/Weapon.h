#pragma once

class CPlayer;
//������Ǘ�����N���X

class CWeapon
{
public:
	enum EnPlayerWeapon
	{
		enSword,			//�Ў茕
		enLongSword,		//���茕
		enArrow,				//�|��
		enTwinSword,		//��
		enWeaponNum
	};

	void Init(CPlayer* player);

	void Update();

	void Draw();

	EnPlayerWeapon GetCurrentState() const
	{
		return m_weaponState;
	}

	const CVector3& GetPosition() const
	{
		return m_worldPos[m_weaponState];
	}

	struct SWeaponStatus
	{
		int attack = 0;
		int diffence = 0;
		EnPlayerWeapon weaponNum;
	};

	/*
	����̃X�e�[�^�X��ݒ�
	status		����̃X�e�[�^�X
	*/
	void SetStatus(SWeaponStatus& status)
	{
		m_weaponStatus[status.weaponNum] = status;
	}
	/*
	����̃X�e�[�^�X���擾
	weaponNum	����̎��
	*/
	const SWeaponStatus& GetStatus(EnPlayerWeapon weaponNum) const
	{
		return m_weaponStatus[weaponNum];
	}

private:
	SWeaponStatus			m_weaponStatus[enWeaponNum];
	const CMatrix*			m_boneMat = nullptr;
	CPlayer*				m_pPlayer = nullptr;
	CVector3				m_position[enWeaponNum];
	CVector3				m_attackPosition[enWeaponNum];
	CQuaternion				m_rotation[enWeaponNum];
	CQuaternion				m_attackRotation[enWeaponNum];
	CVector3				m_worldPos[enWeaponNum];
	CSkinModel				m_weaponskin[enWeaponNum];								//����̃X�L�����f��
	CBoxCollider			m_weaponBoxCollider;									//����p�̃{�b�N�X�R���C�_�[
	CRigidBody				m_weaponRigitBody;										//�{�b�N�X�p��rigidBody
	EnPlayerWeapon			m_weaponState = EnPlayerWeapon::enSword;
};