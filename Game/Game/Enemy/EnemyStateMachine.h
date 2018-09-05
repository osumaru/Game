/*
*	�G�l�~�[�̃X�e�[�g�}�V��
*/

#pragma once

#include "EnemyIdle.h"
#include "EnemyWalk.h"
#include "IEnemyState.h"
#include "EnemyState.h"

class EnemyStateMachine : public IGameObject
{
public:
	//�R���X�g���N�^
	EnemyStateMachine(IEnemy* enemy) :
		m_enemyIdle(enemy, this),
		m_enemyWalk(enemy, this)
	{}

	//�f�X�g���N�^
	~EnemyStateMachine() {}

	//�X�V����O�Ɉ�x�����Ă΂��
	bool Start();

	//�X�V
	void Update() 
	{
	}

	//�X�e�[�g�̐؂�ւ�
	void ChangeState(EnemyState::EnState nextState);

	//���
	void Release();

private:
	EnemyState::EnState m_state = EnemyState::enState_Invald;	//�G�l�~�[�̏��
	IEnemyState*		m_currentState = nullptr;				//���݂̏��
	EnemyIdle			m_enemyIdle;							//�ҋ@
	EnemyWalk			m_enemyWalk;							//����
};