#pragma once
#include "PlayerArrow.h"
#include "Weapon/WeaponManager.h"
#include "WireAction.h"

class CPlayer;
/*
�v���C���[�ƃX�e�[�g�}�V���̊Ԃ����v���C���[�̃t�����h�N���X
*/

class CPlayerGetter
{
public:
	void SetPlayer(CPlayer* player)
	{
		m_pPlayer = player;
	}

	//���C���[�A�N�V�������Ǘ�����N���X���擾
	CWireAction& GetWireAction();

	//���G���ǂ����̃t���O��ݒ�
	void SetIsInvincible(bool isInvincible);

	CAnimation& GetAnimation();

	CCharacterController& GetCharacterController();

	//�_���[�W��Ԃ���������֐�
	void DamageStateReset();

	/*
	�v���C���[�̍��W�̐ݒ�
	*/
	void SetPosition(const CVector3& pos);

	/*
	�v���C���[�̈ړ����x�̐ݒ�
	*/
	void SetMoveSpeed(const CVector3& moveSpeed);

	/*
	���ʂ��ǂ����̃t���O��ݒ�
	*/
	void SetIsDied(bool isDied);

	/*
	�U�����Ă邩�̃t���O��ݒ�
	*/
	void SetIsAttack(bool isAttack);

	//�v���C���[�̃X�s�[�h���擾����
	const CVector3& GetMoveSpeed();

private:
	CPlayer*	m_pPlayer = nullptr;
};
