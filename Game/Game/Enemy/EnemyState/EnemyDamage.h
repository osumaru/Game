/*
*	�G�l�~�[�̃_���[�W�N���X
*/

#pragma once

#include "IEnemyState.h"

class CDamageNumber;

class CEnemyDamage : public IEnemyState
{
public:
	//�R���X�g���N�^
	//enemy		�G�l�~�[�̃C���^�[�t�F�[�X�N���X�̃|�C���^
	//esm		�G�l�~�[�̃X�e�[�g�}�V���N���X�̃|�C���^
	CEnemyDamage(IEnemy* enemy, CEnemyStateMachine* esm) :
		IEnemyState(enemy, esm)
	{
	}

	//�f�X�g���N�^
	~CEnemyDamage() {};

	//������
	void Init();

	//�X�V����O�Ɉ�x�����Ă΂��
	bool Start() override;

	//�X�V
	void Update() override;

	//���
	void Release() override;
private:
	CDamageNumber*	m_damageNumber = nullptr;	//�_���[�W�\��
	CVector3		m_knockBack;
	const float		m_knockBackSpeed = 1.0f;
};