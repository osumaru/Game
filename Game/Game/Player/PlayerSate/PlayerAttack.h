#pragma once
#include"PlayerState.h"
#include "PlayerStateCommon.h"


class CPlayerAttack : public  IPlayerState
{
public:
	//�R���X�g���N�^
	CPlayerAttack();

	//������
	void Init()override;
	
	//
	void Update()override;

private:
	static const int			MAX_ATTACK_NUM = 2;					//�ő�A���U����
	float						m_animetionFrame = 0.0f;			
	int							m_attackCount = 0;					//�A���U�����Ă��
	bool						m_isContinuationAttack = false;		//�A���U�����Ă邩�̃t���O
	EnPlayerAnimation			m_attackAnimation[MAX_ATTACK_NUM];	//�U���̃A�j���[�V�����ԍ�
};

