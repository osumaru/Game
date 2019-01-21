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

	//�m�b�N�o�b�N�����̃t���O���擾
	bool IsNockBack() const
	{
		return m_isNockBack;
	}
private:
	CDamageNumber*	m_damageNumber = nullptr;	//�_���[�W�\��
	const float		m_knockBackSpeed = 5.0f;	//�m�b�N�o�b�N�X�s�[�h
	float			m_deceleration = 0.0f;		//������
	float			m_friction = 0.0f;			//���C��
	float			m_knockBackScale = 1.0f;	//�m�b�N�o�b�N�X�s�[�h�̔{��
	bool			m_wasStanAttack = false;	//�X�^���U�����󂯂���
	bool			m_isNockBack = false;		//�m�b�N�o�b�N�����̃t���O
	CEffect			m_damageEffect;
};