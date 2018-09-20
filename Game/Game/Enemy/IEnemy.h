/*
*	�G�̃C���^�[�t�F�[�X�N���X
*/

#pragma once

#include "../Enemy/EnemyState/EnemyStateMachine.h"
#include "../UI/DamageNumber/DamageNumber.h"
#include "EnemyTurn.h"
#include "EnemySearch.h"

class CEnemyGroup;

struct SEnemyStatus
{
	int Strength;			//�U����
	int Defense;			//�h���
	int	Hp;					//�̗�
	int MaxHp;				//�ő�̗�
	int Gold;				//�������z
};

class IEnemy : public IGameObject
{
public:
	//�R���X�g���N�^
	IEnemy();

	//�f�X�g���N�^
	virtual ~IEnemy();

	//������
	//position	���W
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

	//�N�H�[�^�j�I�����擾
	const CQuaternion& GetRotation() const
	{
		return m_rotation;
	}

	//�N�H�[�^�j�I����ݒ�
	//rotation		�N�H�[�^�j�I��
	void SetRotation(const CQuaternion& rotation)
	{
		m_rotation = rotation;
	}

	//�ړ����x���擾
	const CVector3& GetMoveSpeed() const
	{
		return m_characterController.GetMoveSpeed();
	}

	//�ړ����x��ݒ�
	//moveSpeed		�ړ����x
	void SetMoveSpeed(const CVector3& moveSpeed)
	{
		m_characterController.SetMoveSpeed(moveSpeed);
	}

	//�A�j���[�V�������Đ�
	//animNum	�A�j���[�V�����ԍ�
	void PlayAnimation(int animNum)
	{
		m_animation.Play(animNum, 0.3f);
	}

	//�A�j���[�V�������Đ����Ă��邩
	bool IsPlayAnimation() const
	{
		return m_animation.IsPlay();
	}

	//���[���h�s����擾
	const CMatrix& GetWorldMatrix() const
	{
		return m_skinModel.GetWorldMatrix();
	}

	//�G�l�~�[�̃{�[���̃��[���h�s����擾
	//boneName	�{�[���̖��O
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
	//dmg	�_���[�W���l
	void DamageCalculation(int dmg)
	{
		m_damageNumber.DamageCalculation(dmg);
	}

	//�_���[�W�\���̃��Z�b�g
	void DamageIndicateReset()
	{
		m_damageNumber.Reset();
	}

	//�X�e�[�^�X���擾
	const SEnemyStatus& GetStatus() const
	{
		return m_status;
	}

	//HP�����炷
	//damage	�_���[�W
	void ReduceHp(int damage)
	{
		m_status.Hp -= damage;
	}

	//��������O���[�v��ݒ�
	//enemyGroup	�G�l�~�[�̏�������O���[�v�̃|�C���^
	void SetEnemyGroup(CEnemyGroup* enemyGroup)
	{
		m_enemyGroup = enemyGroup;
	}

	//�������Ă���O���[�v���擾
	CEnemyGroup* GetEnemyGroup()
	{
		return m_enemyGroup;
	}

	//�v���C���[�𔭌�������
	bool IsFind() const
	{
		return m_isFind;
	}

	//�v���C���[�𔭌�������t���O��ݒ肷��
	void SetIsFind(bool isFind)
	{
		m_isFind = isFind;
	}

	//�_���[�W���󂯂���
	bool IsDamage()const
	{
		return m_isDamage;
	}

	//�_���[�W���󂯂����̃t���O��ݒ�
	void SetIsDamage(bool isDamage)
	{
		m_isDamage = isDamage;
	}

protected:
	CSkinModel				m_skinModel;			//�X�L�����f��
	CCharacterController	m_characterController;	//�L�����N�^�[�R���g���[���[
	CAnimation				m_animation;			//�A�j���[�V����
	CEnemyStateMachine		m_enemyStateMachine;	//�X�e�[�g�}�V��
	CEnemyTurn				m_enemyTurn;			//��������]
	CEnemySearch			m_enemySearch;			//�v���C���[��T��
	CDamegeNumber			m_damageNumber;			//�_���[�W���l
	CEnemyGroup*			m_enemyGroup;			//�G�l�~�[�O���[�v
	CVector3				m_position;				//���W
	CQuaternion				m_rotation;				//��]
	SEnemyStatus			m_status;				//�X�e�[�^�X
	int						m_animNum = 0;			//�Đ�����A�j���[�V�����ԍ�
	int						m_animNumOld = 0;		//1�O�̃A�j���[�V�����ԍ�
	bool					m_isAttackHit = false;	//�U��������������
	bool					m_isFind = false;		//�v���C���[�𔭌�������
	bool					m_isDamage = false;		//�_���[�W���󂯂����̔���
};