/*
*	�G�l�~�[�̃X�^���N���X
*/
#pragma once

#include "IEnemyState.h"

class CDamageNumber;

class CEnemyStan : public IEnemyState
{
public:
	//�R���X�g���N�^
	//enemy		�G�l�~�[�̃C���^�[�t�F�[�X�N���X�̃|�C���^
	//esm		�G�l�~�[�̃X�e�[�g�}�V���N���X�̃|�C���^
	CEnemyStan(IEnemy* enemy, CEnemyStateMachine* esm) :
		IEnemyState(enemy, esm) 
	{
	}

	//�f�X�g���N�^
	~CEnemyStan()
	{
	}

	//�X�V�����O�Ɉ�x�����Ă΂��
	bool Start() override;

	//�X�V
	void Update() override;
private:
	CDamageNumber*	m_damageNumber = nullptr;	//�_���[�W�\��
	float			m_timer = 0.0f;				//�^�C�}�[
};