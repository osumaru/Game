#pragma once
#include"PlayerState.h"
#include "PlayerStateCommon.h"
//�v���C���[�̍U��(�R���{�U�������܂�)�̃X�e�[�g

class CPlayerAttack : public  IPlayerState
{
public:
	//�R���X�g���N�^
	CPlayerAttack();

	//������
	void Init()override;
	
	//�X�V
	void Update()override;

	//�ړ�
	void Move();

	//��]
	void Rotation();

	//���`�⊮
	void Lerp();

	//�A���U�����Ă���񐔂��擾
	int GetAttackCount() const
	{
		return m_attackCount;
	}

private:
	int							m_maxAttackNum = 0;					//�ő�A���U����
	int							m_attackCount = 0;					//�A���U�����Ă��
	bool						m_isContinuationAttack = false;		//�A���U�����Ă邩�̃t���O
	EnPlayerAnimation*			m_attackAnimation;					//�U���̃A�j���[�V�����ԍ�
	EnPlayerAnimation*			m_combineAnimation;					//�U���̌�̍����p�̃A�j���[�V�����ԍ�
	bool*						m_stanAttack;						//�X�^���U��
	int							m_maxWeaponHitNum;					//���킲�Ƃ̍U����
	const CMatrix*				m_pBoneMat;							//�{�[���̍s��̃|�C���^
	CQuaternion					m_addRot;
	CVector3					m_rotationDirectionVector;
};

