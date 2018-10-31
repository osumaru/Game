#pragma once

enum EnPlayerAnimation
{
	enPlayerAnimationStand,			//�ҋ@�A�j���[�V����
	enPlayerAnimationWalk,			//���s�A�j���[�V����
	enPlayerAnimationRun,			//����A�j���[�V����
	enPlayerAnimationRunJump,		//����W�����v
	enPlayerAnimationJump,			//�W�����v�A�j���[�V����
	enPlayerAnimationAttack,		//�U���A�j���[�V����
	enPlayerAnimationAttack2,		//�A���A�j���[�V����
	enPlayerAnimationDamage,		//�_���[�W�A�j���[�V����
	enPlayerAnimationAvoidance,		//����A�j���[�V����
	enPlayerAnimationDete,			//���S�A�j���[�V����
	enPlayerAnimationWireMove,		//���C���[�ړ��A�j���[�V����
	enPlayerAnimationArrowAttack,	//�|�̃A�j���[�V����
	enPlayerAnimationArrowShoot,	//�|����A�j���[�V����
	enPlayerAnimationLongSwordAttack,//�匕�̍U���A�j���[�V����
	enPlayerAnimationTwinSwordAttack,//�񓁗��̍U���A�j���[�V����
	enPlayerAnimationNum				//�A�j���[�V�����̐�
};

class CPlayerState
{
public:
	enum EnPlayerState
	{
		enPlayerStateStand,				//�ҋ@�A�j���[�V����
		enPlayerStateWalk,				//���s�A�j���[�V����
		enPlayerStateRun,				//����A�j���[�V����
		enPlayerStateRunJump,			//����W�����v
		enPlayerStateJump,				//�W�����v�A�j���[�V����
		enPlayerStateAttack,			//�U���A�j���[�V����
		enPlayerStateDamage,			//�_���[�W�A�j���[�V����
		enPlayerStateAvoidance,			//����A�j���[�V����
		enPlayerStateDied,				//���S�A�j���[�V����
		enPlayerStateWireMove,			//���C���[�A�j���[�V����
		enPlayerStateArrowAttack,		//�|�̃A�j���[�V����
		enPlayerStateArrowShoot,		//�|����A�j���[�V����
		enPlayerStateLongSwordAttack,	//�匕�̍U���A�j���[�V����
		enPlayerStateTwinSwordAttack,	//�񓁗��̍U���A�j���[�V����
		enPlayerStateNum,				//�A�j���[�V�����̐�
	};

	enum EnPlayerWepon
	{
		enSword,			//�Ў茕
		enLongSword,		//���茕
		enArro,				//�|��
		enTwinSword,		//��

	};
};