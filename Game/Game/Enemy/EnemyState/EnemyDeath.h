/*
*	�G�l�~�[�̎��S�N���X
*/

#pragma once

#include "IEnemyState.h"

class CEnemyDeath : public IEnemyState
{
public:
	//�R���X�g���N�^
	//enemy		�G�l�~�[�̃C���^�[�t�F�[�X�N���X�̃|�C���^
	//esm		�G�l�~�[�̃X�e�[�g�}�V���N���X�̃|�C���^
	CEnemyDeath(IEnemy* enemy, CEnemyStateMachine* esm) :
		IEnemyState(enemy, esm)
	{
	}

	//�f�X�g���N�^
	~CEnemyDeath() {}

	//�X�V����O�Ɉ�x�����Ă΂��
	bool Start() override;

	//�X�V
	void Update() override;

	//�A�j���[�V�������I��������
	bool GetIsAnimationEnd()
	{
		return m_isAnimationEnd;
	}

private:
	bool m_isAnimationEnd = false;	//�A�j���[�V�������I��������
};