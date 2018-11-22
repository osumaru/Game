#pragma once

class CCameraCollisionSolver {
public:
	//�R���X�g���N�^
	CCameraCollisionSolver();

	//�f�X�g���N�^
	~CCameraCollisionSolver();

	//������
	//radius	�J�����̃o�E���f�B���O�X�t�B�A�̔��a
	void Init(float radius);

	//�R���W���������̎��s
	//result	�R���W�����������s�������ʂ̃J�����̎��_�̍��W���i�[�����
	//posiiton	�J�����̎��_
	//target	�J�����̒����_
	//return	�R���W�����������s�����ꍇ��true���Ԃ��Ă���
	bool Execute(CVector3& result, const CVector3& position, const CVector3& target);
private:
	CSphereCollider	m_collider;		 //�R���C�_�[
	float			m_radius = 0.0f; //���a
};