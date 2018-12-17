/*
*	�G�̃C���^�[�t�F�[�X�N���X
*/

#pragma once

#include "EnemyState/EnemyStateMachine.h"
#include "EnemyTurn.h"
#include "EnemySearch.h"
#include "../Player/Weapon/WeaponCommon.h"

class CEnemyGroup;

struct SEnemyStatus
{
	int strength;	//�U����
	int defense;	//�h���
	int	hp;			//�̗�
	int maxHp;		//�ő�̗�
	int gold;		//�������z
	int exp;		//�o���l
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
	virtual void Init(CVector3 position) {};

	//�X�V
	virtual void Update() = 0;

	//�`��
	virtual void Draw() {};

	void AddObject()
	{
		Add(&m_enemyStateMachine, 0);
		Add(&m_enemyTurn, 0);
		Add(&m_enemySearch, 0);
	}

	//���ʑO�ɌĂ΂��֐��A��������ȂǂɎg��
	void BeforeDead()override;

	//�G�̌����Ă������������͈̔͂ɓ����Ă��邩���肷��
	//degree	�p�x(�f�O���[)
	//position	���͈̔͂ɂ��邩���ׂ������W
	bool CalucFanShape(float degree, const CVector3& position);

	//���g���G�l�~�[���X�g����폜
	void EnemyListErase();

	//�����蔻��p�̍��̍��W���X�V
	void UpdateSpinePos();

	//�G�̍U��(�G�̎�ނɂ���ĕς��)
	virtual void Attack() {};

	//���g�̃C�e���[�^��ݒ�
	void SetIterater(std::list<IEnemy*>::iterator iterater)
	{
		m_iterater = iterater;
	}

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

	//���̂��폜
	void RemovedRegidBody()
	{
		m_isRemovedRigidBody = true;
		m_characterController.RemovedRigidBody();
	}

	//�A�j���[�V�������擾
	CAnimation& GetAnimation()
	{
		return m_animation;
	}

	//���[���h�s����擾
	const CMatrix& GetWorldMatrix() const
	{
		return m_skinModel.GetWorldMatrix();
	}

	//�����蔻��p�̍��̃��[���h�s����擾
	const CVector3& GetSpinePos() const
	{
		return m_spinePos;
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

	//�X�e�[�^�X���擾
	const SEnemyStatus& GetStatus() const
	{
		return m_status;
	}

	//HP�����炷
	//damage	�_���[�W
	void HpDamage(int damage)
	{
		m_status.hp -= damage;
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
	bool IsDamage() const
	{
		return m_isDamage;
	}

	//�_���[�W���󂯂���t���O��ݒ肷��
	void SetIsDamage(bool isDamage)
	{
		m_isDamage = isDamage;
	}

	//�_���[�W���󂯂��邩
	bool IsDamagePossible() const
	{
		return m_isDamagePossible;
	}

	//�_���[�W���󂯂��邩�̃t���O��ݒ肷��
	void SetIsDamagePossible(bool isDamage)
	{
		m_isDamagePossible = isDamage;
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

	//�U���ł��鋗�����擾
	float GetAttackLength()
	{
		return m_attackLength;
	}

	//�U���ł��鋗����ݒ�
	void SetAttackLength(float attackLength)
	{
		m_attackLength = attackLength;
	}

	//�U���^�C�v
	enum EnAttackType
	{
		enAttackType_Far,
		enAttackType_Near,
	};

	//�U���^�C�v���擾
	EnAttackType GetAttackType()
	{
		return m_attackType;
	}

	//�U�����ꂽ������擾
	EnAttackWeapon GetAttackWeapon()
	{
		return m_attackWeapon;
	}

	//�U�����ꂽ�����ݒ�
	void SetAttackWeapon(EnAttackWeapon AttackWeapon)
	{
		m_attackWeapon=AttackWeapon;
	}

protected:
	CSkinModel						m_skinModel;					//�X�L�����f��
	CAnimation						m_animation;					//�A�j���[�V����
	CEnemyStateMachine				m_enemyStateMachine;			//�X�e�[�g�}�V��
	CEnemyTurn						m_enemyTurn;					//��������]
	CEnemySearch					m_enemySearch;					//�v���C���[��T��
	CEnemyGroup*					m_enemyGroup;					//�G�l�~�[�O���[�v
	CVector3						m_position;						//���W
	CQuaternion						m_rotation;						//��]
	CCharacterController			m_characterController;			//�L�����N�^�[�R���g���[���[
	SEnemyStatus					m_status;						//�X�e�[�^�X
	EnAttackType					m_attackType = enAttackType_Near; //�U���^�C�v
	std::list<IEnemy*>::iterator	m_iterater;						//���g�̃C�e���[�^
	const CMatrix*					m_spineMatrix;					//�����蔻��p�̍��̃��[���h�s��
	CVector3						m_spinePos;						//�����蔻��p�̍��̍��W
	float							m_attackLength = 1.2f;			//�U���ł��鋗��
	bool							m_isFind = false;				//�v���C���[�𔭌�������
	bool							m_isDamage = false;				//�_���[�W���󂯂���
	bool							m_isDamagePossible = true;		//�_���[�W���󂯂��邩
	bool							m_isWireHit = false;			//���C���[������������
	bool							m_isRemovedRigidBody = false;	//���̂��폜���ꂽ��
	EnAttackWeapon					m_attackWeapon=enAttackWeaponNone;	//�U�����镐��
};