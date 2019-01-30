/*
*	�G�l�~�[�̍U����̑҂���ԃN���X
*/

#pragma once

#include "IEnemyState.h"

class CEnemyAttackWait : public IEnemyState
{
public:
	//�R���X�g���N�^
	//enemy		�G�l�~�[�̃C���^�[�t�F�[�X�N���X�̃|�C���^
	//esm		�G�l�~�[�̃X�e�[�g�}�V���N���X�̃|�C���^
	CEnemyAttackWait(IEnemy* enemy, CEnemyStateMachine* esm) :
		IEnemyState(enemy, esm)
	{
	}

	//�f�X�g���N�^
	~CEnemyAttackWait()
	{
	}

	//�X�V�����O�Ɉ�x�����Ă΂��֐�
	bool Start() override;

	//�X�V
	void Update() override;

	//��]
	void Rotation();
private:
	float m_timer = 0.0f;	//�^�C�}�[
	bool  m_isNoneEnd = false; //�������Ȃ���Ԃ��I�������
};