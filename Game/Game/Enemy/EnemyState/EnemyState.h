/*
*	�G�l�~�[�̏�ԃN���X
*/

#pragma once

class EnemyState {
public:
	enum EnState {
		enState_Idle,	//�ҋ@
		enState_Walk,	//����
		enState_Attack,	//�U��
		enState_Damage,	//�_���[�W
		enState_Death,	//���S
		enState_Invald,	//�����Ȃ�
	};
};