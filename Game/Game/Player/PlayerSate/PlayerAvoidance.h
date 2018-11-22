#pragma once
#include "PlayerState.h"

class CPlayerAvoidance: public IPlayerState
{
public:
	//������
	void Init()override;

	//�X�V����
	void Update()override;

	//�ړ�����
	void Move();

	//��]
	void Rotation();
private:
	const CMatrix* m_pBoneMat;	//�{�[���̍s��̃|�C���^
	CVector3 m_manipVec;		//�{�[���̍��W����v���C���[�̍��W�܂ł̃x�N�g��
	CVector3 m_preBonePos;		//�O�̃t���[���̃{�[���̍��W
};

