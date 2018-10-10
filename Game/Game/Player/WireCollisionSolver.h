/*
*	���C���[�̓����蔻��N���X
*/

#pragma once

#include "../../../osumaruEngine/Physics/Collider/CapsuleCollider.h"

class CWireCollisionSolver
{
public:
	//�R���X�g���N�^
	CWireCollisionSolver();

	//�f�X�g���N�^
	~CWireCollisionSolver();

	//������
	//radius	�J�v�Z���R���C�_�[�̔��a
	//height	�J�v�Z���R���C�_�[�̍���
	void Init(float radius, float height);

	//�R���W���������̎��s
	//position	�v���C���[�̍��W
	//target	���C���[�̈ړ���̍��W
	bool Execute(const CVector3& position, const CVector3 target);

private:
	CCapsuleCollider	m_collider;			//�R���C�_�[
	float				m_radius = 0.0f;	//���a
	float				m_height = 0.0f;	//����
};