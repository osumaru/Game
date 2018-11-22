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

	void Move();

private:
	static const int			MAX_ATTACK_NUM = 3;					//�ő�A���U����
	int							m_attackCount = 0;					//�A���U�����Ă��
	bool						m_isContinuationAttack = false;		//�A���U�����Ă邩�̃t���O
	EnPlayerAnimation			m_attackAnimation[MAX_ATTACK_NUM];	//�U���̃A�j���[�V�����ԍ�
	EnPlayerAnimation			m_combineAnimation[MAX_ATTACK_NUM];	//�U���̌�̍����p�̃A�j���[�V�����ԍ�
	bool						m_isPreDodge = false;				//����̐�s���͗p�t���O

	const CMatrix* m_pBoneMat;	//�{�[���̍s��̃|�C���^
	CVector3 m_manipVec;		//�{�[���̍��W����v���C���[�̍��W�܂ł̃x�N�g��
	CVector3 m_preBonePos;		//�O�̃t���[���̃{�[���̍��W
};

