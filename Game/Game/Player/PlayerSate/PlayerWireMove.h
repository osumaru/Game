/*
*	�v���C���[�̃��C���[�ړ��N���X
*/

#pragma once

#include "IPlayerState.h"

class CPlayerWireMove : public IPlayerState
{
public:
	//�R���X�g���N�^
	CPlayerWireMove() {}

	//�f�X�g���N�^
	~CPlayerWireMove() {}

	//�X�V�����O�Ɉ�x�����Ă΂��
	bool Start();

	//�X�V
	void Update();

private:
	CVector3	m_movePosition;		//�ړ���̍��W
	const float m_speed = 20.0f;	//�ړ����x
};