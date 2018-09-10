/*
*	�G�̃C���^�[�t�F�[�X�N���X
*/

#pragma once

#include "../Enemy/EnemyState/EnemyStateMachine.h"
#include "../UI/DamageNumber/DamageNumber.h"

class IEnemy : public IGameObject
{
public:
	//�R���X�g���N�^
	IEnemy();

	//�f�X�g���N�^
	virtual ~IEnemy();

	//������
	virtual void Init(CVector3 position) = 0;

	//�X�V
	virtual void Update() = 0;

	//�`��
	virtual void Draw() = 0;

	//�G�̍��W���擾
	const CVector3& GetPosition() const
	{
		return m_position;
	}

	//�Đ��������A�j���[�V�����̔ԍ���ݒ�
	void SetAnimNum(int animNum)
	{
		m_animNum = animNum;
	}

	//�A�j���[�V�������Đ�
	void PlayAnimation(int animNum)
	{
		m_animation.Play(animNum);
	}

	//�A�j���[�V�������Đ����Ă��邩
	bool IsPlayAnimation() const
	{
		return m_animation.IsPlay();
	}

	//�G�l�~�[�̃{�[���̃��[���h�s����擾
	const CMatrix& GetBoneWorldMatrix(const wchar_t* boneName) const
	{
		return m_skinModel.FindBoneWorldMatrix(boneName);
	}

	//�X�e�[�g�}�V�����Q�[���I�u�W�F�N�g������
	void StateMachineRelease()
	{
		m_enemyStateMachine.Release();
	}

	//�G�l�~�[�̃_���[�W�v�Z
	void DamageCalculation()
	{
		m_damageNumber.DamageCalculation();
	}

	//�_���[�W�\���̃��Z�b�g
	void DamageIndicateReset()
	{
		m_damageNumber.Reset();
	}

protected:
	CSkinModel				m_skinModel;			//�X�L�����f��
	CCharacterController	m_characterController;	//�L�����N�^�[�R���g���[���[
	CAnimation				m_animation;			//�A�j���[�V����
	EnemyStateMachine		m_enemyStateMachine;	//�X�e�[�g�}�V��
	CDamegeNumber			m_damageNumber;			//�_���[�W���l
	CVector3				m_position;				//���W
	CQuaternion				m_rotation;				//��]
	int						m_animNum = 0;			//�Đ�����A�j���[�V�����ԍ�
	int						m_animNumOld = 0;		//1�O�̃A�j���[�V�����ԍ�
};