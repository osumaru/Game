#pragma once
#include "PlayerArrow.h"
#include "Weapon/WeaponManager.h"
#include "WireAction.h"
#include "WireDraw.h"

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

	//�X�^���_���[�W��Ԃ���������֐�
	void StanDamageStateReset();
	/*
	�v���C���[�̍��W�̐ݒ�
	*/
	void SetPosition(const CVector3& pos);

	//�v���C���[�̃N�H�[�^�j�I�����擾
	const CQuaternion& GetRotation();

	//�v���C���[�̃N�H�[�^�j�I����ݒ�
	void SetRotation(const CQuaternion& rotation);

	/*
	�v���C���[�̈ړ����x�̐ݒ�
	*/
	void SetMoveSpeed(const CVector3& moveSpeed);

	/*
	���ʂ��ǂ����̃t���O��ݒ�
	*/
	void SetIsDied(bool isDied);

	/*
	�X�L�����f���̃A�b�v�f�[�g
	*/
	void SkinModelUpdate();

	/*
	�U�����Ă邩�̃t���O��ݒ�
	*/
	void SetIsAttack(bool isAttack);

	//�v���C���[�̃X�s�[�h���擾����
	const CVector3& GetMoveSpeed();

	//�X�e�B�b�N�̓��͕�����ݒ�
	void SetStickDir(const CVector3& stickDir);

	//�X�e�B�b�N�̓��͕������擾
	const CVector3& GetStickDir();

	void SetDamageEnemyPos(const CVector3& position);

	const CVector3& GetDamageEnemyPos();

	CWireDraw& GetWireDraw();

private:
	CPlayer*	m_pPlayer = nullptr;
	CVector3	m_stickDir;
	CVector3	m_damageEnemyPos;
};
