/*
*	�G�l�~�[�̒Ǐ]�N���X
*/

#pragma once

#include "IEnemyState.h"

class CEnemyChase : public IEnemyState
{
public:
	//�R���X�g���N�^
	//enemy		�G�l�~�[�̃C���^�[�t�F�[�X�N���X�̃|�C���^
	//esm		�G�l�~�[�̃X�e�[�g�}�V���N���X�̃|�C���^
	CEnemyChase(IEnemy* enemy, CEnemyStateMachine* esm) :
		IEnemyState(enemy, esm)
	{
	}

	//�f�X�g���N�^
	~CEnemyChase() {}

	//�X�V����O�Ɉ�x�����Ă΂��
	bool Start() override;

	//�X�V
	void Update() override;

	//�ړ�
	void Move(float length);

private:
	std::vector<CVector3> m_root;				//���[�g�̍��W��ۑ����Ă��郊�X�g
	std::vector<CVector3>::iterator m_iterater;	//�C�e���[�^
	int	m_interval = 0;							//�C���^�[�o��
};
