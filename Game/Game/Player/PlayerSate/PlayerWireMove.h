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
	bool		m_isWireThrow = true;	//���C���[�𓊂��Ă��邩
	const CMatrix*	m_playerHandMatrix;	//�v���C���[�̎�̃��[���h�s��
	CVector3	m_playerHandPos = CVector3::Zero; //�v���C���[�̎�̍��W
	float		m_wireSpeed = 1.0f;		//���C���[�𓊂���X�s�[�h
	CVector3	m_previousMoveSpeed;	//�O�̃t���[���̈ړ����x
	float		m_gravityBackup = 0.0f;	//���n��ɏd�͂�߂����߂Ɏg���ϐ�
};