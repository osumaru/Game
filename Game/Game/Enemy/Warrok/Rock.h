/*
*	�G���������N���X
*/

#pragma once

class CWarrok;

class CRock : public IGameObject
{
public:
	//�R���X�g���N�^
	CRock() {};

	//�f�X�g���N�^
	~CRock() {};

	//������
	//warrok		�G�l�~�[�̃|�C���^
	//enemyPos		�G�l�~�[�̍��W
	void Init(CWarrok* warrok, const CVector3& enemyPos);

	//�X�V
	void Update();

	//�`��
	void Draw();

	//�ړ����x��ݒ�
	void SetMoveSpeed();

	//�������Ă��邩��ݒ�
	void SetIsThrow(bool isThrow)
	{
		m_isThrow = isThrow;
	}

	//�������Ă��邩���擾
	bool GetIsThrow()
	{
		return m_isThrow;
	}

private:
	CSkinModel				m_skinModel;			//�X�L�����f��
	CCharacterController	m_characterController;	//�L�����N�^�[�R���g���[���[
	CVector3				m_position;				//���W
	CQuaternion				m_rotation;				//��]
	CVector3				m_targetPos;			//�^�[�Q�b�g�̍��W
	CWarrok*				m_warrok;				//�G�l�~�[
	CVector3				m_enemyPos;				//�G�̍��W
	const CMatrix*			m_enemyHandMatrix;		//�G�̎�̍s��
	bool					m_isThrow = false;		//�������Ă��邩
	bool					m_isHit = false;		//�����ɓ�������
	SParticleEmittInfo		m_particleInfo;			//�p�[�e�B�N���̏��
};