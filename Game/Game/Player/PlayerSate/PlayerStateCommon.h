#pragma once

//�v���C���[�A�j���[�V�����̗񋓌^
enum EnPlayerAnimation
{
	enPlayerAnimationStand,			//�ҋ@�A�j���[�V����
	enPlayerAnimationWalk,			//���s�A�j���[�V����
	enPlayerAnimationRun,			//����A�j���[�V����
	enPlayerAnimationRunJump,		//����W�����v
	enPlayerAnimationJump,			//�W�����v�A�j���[�V����
	enPlayerAnimationAttack1,		//�U���A�j���[�V����
	enPlayerAnimationAttack2,		//�A���A�j���[�V����
	enPlayerAnimationAttack3,		//�A���A�j���[�V����
	enPlayerAnimationAttackCombine1,		//�A���̌�̍����p�A�j���[�V����
	enPlayerAnimationAttackCombine2,		//�A���̌�̍����p�A�j���[�V����
	enPlayerAnimationAttackCombine3,		//�A���̌�̍����p�A�j���[�V����
	enPlayerAnimationAttackAir,		//�U��(��)�A�j���[�V����
	enPlayerAnimationStun,			//�X�^���p�̃A�j���[�V����
	enPlayerAnimationDamage,		//�_���[�W�A�j���[�V����
	enPlayerAnimationDamageAir,		//�_���[�W(��)�A�j���[�V����
	enPlayerAnimationAvoidance,		//����A�j���[�V����
	enPlayerAnimationAvoidanceCombine,	//����̌�̍����p�|�[�Y�̃A�j���[�V����
	enPlayerAnimationDete,			//���S�A�j���[�V����
	enPlayerAnimationWireMove,		//���C���[�ړ��A�j���[�V����
	enPlayerAnimationWireAttack,	//���C���[�U���A�j���[�V����
	enPlayerAnimationArrowAttack,	//�|�̃A�j���[�V����
	enPlayerAnimationArrowShoot,	//�|����A�j���[�V����
	enPlayerAnimationLongSwordAttack,//�匕�̍U���A�j���[�V����
	enPlayerAnimationTwinSwordAttack,//�񓁗��̍U���A�j���[�V����
	enPlayerAnimationLanding,//���n�A�j���[�V����
	enPlayerAnimationNum			//�A�j���[�V�����̐�
};


class CPlayerState
{
public:
	//�X�e�[�g�}�V���̗񋓌^
	enum EnPlayerState
	{
		enPlayerStateStand,				//�ҋ@�X�e�[�g
		enPlayerStateWalk,				//���s�X�e�[�g
		enPlayerStateRun,				//����X�e�[�g
		enPlayerStateRunJump,			//����W�����v
		enPlayerStateJump,				//�W�����v�X�e�[�g
		enPlayerStateAttack,			//�U���X�e�[�g
		enPlayerStateDamage,			//�_���[�W�X�e�[�g
		enPlayerStateStun,				//�X�^���X�e�[�g
		enPlayerStateAvoidance,			//����X�e�[�g
		enPlayerStateDied,				//���S�X�e�[�g
		enPlayerStateWireMove,			//���C���[�X�e�[�g
		enPlayerStateWireAttack,		//���C���[�U���X�e�[�g
		enPlayerStateArrowAttack,		//�|�̃X�e�[�g
		enPlayerStateArrowShoot,		//�|����X�e�[�g
		enPlayerStateLongSwordAttack,	//�匕�̍U���X�e�[�g
		enPlayerStateTwinSwordAttack,	//�񓁗��̍U���X�e�[�g
		enPlayerStateNum,				//�X�e�[�g�̐�
	};
};