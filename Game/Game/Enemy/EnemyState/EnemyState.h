/*
*	�G�l�~�[�̏�ԃN���X
*/

#pragma once

class CEnemyState {
public:
	enum EnState {
		enState_Idle,		//�ҋ@
		enState_Walk,		//����
		enState_Chase,		//�Ǐ]
		enState_Attack,		//�U��
		enState_AttackWait,	//�U����̑҂�
		enState_Damage,		//�_���[�W
		enState_Stan,		//�X�^��
		enState_Death,		//���S
		enState_Num,		//��Ԃ̐�
		enState_Invald,		//�����Ȃ�
	};

	enum EnAnimationState {
		enAnimation_Idle,	//�ҋ@
		enAnimation_Walk,	//����
		enAnimation_Chase,	//�Ǐ]
		enAnimation_Attack,	//�U��
		enAnimation_Damage,	//�_���[�W
		enAnimation_Death,	//���S
		enAnimation_Num,	//��Ԃ̐�
	};
};