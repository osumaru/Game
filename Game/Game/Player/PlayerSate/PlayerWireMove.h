/*
*	�v���C���[�̃��C���[�ړ��N���X
*/

#pragma once

#include "PlayerState.h"

class CPlayerWireMove : public IPlayerState
{
public:
	//�R���X�g���N�^
	CPlayerWireMove() {}

	//�f�X�g���N�^
	~CPlayerWireMove() {}

	void Init()override;

	//�X�V
	void Update()override;

private:
	CVector3	m_movePosition;		//�ړ���̍��W
	const float m_speed = 40.0f;	//�ړ����x
	float		m_accel = 0.0f;
	float		m_moveSpeed = 0.0f;
	bool		m_isWireThrow = true;
};