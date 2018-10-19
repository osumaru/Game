/*
*	�G�̃C���^�[�t�F�[�X�N���X
*/

#pragma once

#include "EnemyState/EnemyStateMachine.h"
#include "EnemyMove.h"
#include "EnemyTurn.h"
#include "EnemySearch.h"
#include "../UI/DamageNumber/DamageNumber.h"

class CEnemyGroup;
class CRootPoint;

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

	//�G�̍��W��ݒ�
	void SetPosition(const CVector3& position)
	{
		m_position = position;
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

	//�_���[�W�v�Z���s��
	//damage	�_���[�W�̒l
	void DamageCaluc(int damage)
	{
		m_damageNumber.DamageCalculation(damage);
	}

	//�_���[�W�\������߂�
	void DamageIndicateReset()
	{
		m_damageNumber.IndicateReset();
	}

	//�_���[�W�\���̍��W��ݒ�
	void SetDamageCalucPos(const CVector2& position)
	{
		m_damageNumber.SetPosition(position);
	}

	//�X�e�[�^�X���擾
	const SEnemyStatus& GetStatus() const
	{
		return m_status;
	}

	//HP�����炷
	//damage	�_���[�W
	void HpDamage(int damage)
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

	//���[�g��̃G�l�~�[������|�C���g��ݒ�
	//rootPoint		�G�l�~�[������|�C���g
	void SetRootPoint(CRootPoint* rootPoint)
	{
		m_rootPoint = rootPoint;
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
	bool IsDamage() const
	{
		return m_isDamage;
	}

	//�_���[�W���󂯂���t���O��ݒ肷��
	void SetIsDamage(bool isDamage)
	{
		m_isDamage = isDamage;
	}

	//���C���[������������
	bool IsWireHit() const
	{
		return m_isWireHit;
	}

	//���C���[������������t���O��ݒ肷��
	void SetIsWireHit(bool isWireHit)
	{
		m_isWireHit = isWireHit;
	}

protected:
	CSkinModel				m_skinModel;			//�X�L�����f��
	CCharacterController	m_characterController;	//�L�����N�^�[�R���g���[���[
	CAnimation				m_animation;			//�A�j���[�V����
	CEnemyStateMachine		m_enemyStateMachine;	//�X�e�[�g�}�V��
	CEnemyMove				m_enemyMove;			//�ړ�
	CEnemyTurn				m_enemyTurn;			//��������]
	CEnemySearch			m_enemySearch;			//�v���C���[��T��
	CEnemyGroup*			m_enemyGroup;			//�G�l�~�[�O���[�v
	CRootPoint*				m_rootPoint;			//���[�g�|�C���g
	CDamageNumber			m_damageNumber;			//�_���[�W���l
	CVector3				m_position;				//���W
	CQuaternion				m_rotation;				//��]
	SEnemyStatus			m_status;				//�X�e�[�^�X
	int						m_animNum = 0;			//�Đ�����A�j���[�V�����ԍ�
	int						m_animNumOld = 0;		//1�O�̃A�j���[�V�����ԍ�
	bool					m_isAttackHit = false;	//�U��������������
	bool					m_isFind = false;		//�v���C���[�𔭌�������
	bool					m_isDamage = false;		//�_���[�W���󂯂���
	bool					m_isWireHit = false;	//���C���[������������
};