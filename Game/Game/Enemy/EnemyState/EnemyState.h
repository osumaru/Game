/*
*	�G�l�~�[�̏�ԃN���X
*/

#pragma once

class CEnemyState {
public:
	enum EnState {
		enState_Idle,	//�ҋ@
		enState_Walk,	//����
		enState_Chase,	//�Ǐ]
		enState_Attack,	//�U��
		enState_Damage,	//�_���[�W
		enState_Death,	//���S
		enState_Num,	//��Ԃ̐�
		/////////////
		enState_Stan,	//�X�^��
		/////////////
		enState_Invald,	//�����Ȃ�
	};
};