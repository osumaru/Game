/*
*	�G�l�~�[�̃X�e�[�g�̃C���^�[�t�F�[�X
*/

#pragma once

#include "stdafx.h"

class IEnemy;
class EnemyStateMachine;

class IEnemyState : public IGameObject
{
public:
	//�R���X�g���N�^
	//enemy		�G�l�~�[�̃C���^�[�t�F�[�X�N���X�̃|�C���^
	//esm		�G�l�~�[�̃X�e�[�g�}�V���N���X�̃|�C���^
	IEnemyState(IEnemy* enemy, EnemyStateMachine* esm) :
		m_enemy(enemy),
		m_esm(esm)
	{
	}

	//�f�X�g���N�^
	virtual ~IEnemyState() {}

	//�X�V
	virtual void Update() = 0;

protected:
	IEnemy*				m_enemy = nullptr;	//�G�l�~�[
	EnemyStateMachine*	m_esm = nullptr;	//�X�e�[�g�}�V��
};