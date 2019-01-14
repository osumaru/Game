/*
*	�G�l�~�[�̃X�e�[�g�}�V��
*/

#pragma once

#include "EnemyIdle.h"
#include "EnemyWalk.h"
#include "EnemyChase.h"
#include "EnemyAttack.h"
#include "EnemyDamage.h"
#include "EnemyDeath.h"
#include "EnemyStan.h"
#include "EnemyAttackWait.h"
#include "IEnemyState.h"
#include "EnemyState.h"

class CEnemyGroup;

class CEnemyStateMachine : public IGameObject
{
public:
	//�R���X�g���N�^
	//enemy		�G�l�~�[�̃C���^�[�t�F�[�X�N���X�̃|�C���^
	CEnemyStateMachine(IEnemy* enemy) :
		m_enemyIdle(enemy, this),
		m_enemyWalk(enemy, this),
		m_enemyChase(enemy, this),
		m_enemyAttack(enemy, this),
		m_enemyDamage(enemy, this),
		m_enemyDeath(enemy, this),
		m_enemyStan(enemy, this),
		m_enemyAttackWait(enemy, this)
	{
	}

	//�f�X�g���N�^
	virtual ~CEnemyStateMachine() {}

	//�X�V����O�Ɉ�x�����Ă΂��
	bool Start() override;

	//�X�V
	void Update() override;

	//�X�e�[�g�̐؂�ւ�
	void ChangeState(CEnemyState::EnState nextState);

	//���
	void Release();

	//��������O���[�v��ݒ�
	//enemyGroup		��������O���[�v�̃|�C���^
	void SetEnemyGroup(CEnemyGroup* enemyGroup)
	{
		m_enemyGroup = enemyGroup;
	}

	//�X�e�[�g���擾
	const IEnemyState* GetState(CEnemyState::EnState state) const
	{
		switch (state)
		{
		case CEnemyState::enState_Attack:
			return &m_enemyAttack;

		case CEnemyState::enState_AttackWait:
			return &m_enemyAttackWait;

		case CEnemyState::enState_Chase:
			return &m_enemyChase;

		case CEnemyState::enState_Damage:
			return &m_enemyDamage;

		case CEnemyState::enState_Death:
			return &m_enemyDeath;

		case CEnemyState::enState_Idle:
			return &m_enemyIdle;

		case CEnemyState::enState_Stan:
			return &m_enemyStan;

		case CEnemyState::enState_Walk:
			return &m_enemyWalk;
		}
	}

private:
	CEnemyState::EnState	m_state = CEnemyState::enState_Invald;	//�G�l�~�[�̏��
	IEnemyState*			m_currentState = nullptr;				//���݂̏��
	CEnemyIdle				m_enemyIdle;							//�ҋ@
	CEnemyWalk				m_enemyWalk;							//����
	CEnemyChase				m_enemyChase;							//�Ǐ]
	CEnemyAttack			m_enemyAttack;							//�U��
	CEnemyDamage			m_enemyDamage;							//�_���[�W
	CEnemyDeath				m_enemyDeath;							//���S
	CEnemyStan				m_enemyStan;							//�X�^��
	CEnemyAttackWait		m_enemyAttackWait;						//�U����̑҂�
	CEnemyGroup*			m_enemyGroup = nullptr;					//�G�l�~�[�O���[�v
};