/*
*	�G���������N���X
*/

#pragma once

class IEnemy;

class CRock : public IGameObject
{
public:
	//�R���X�g���N�^
	CRock() {};

	//�f�X�g���N�^
	~CRock() {};

	//������
	//handMatrix	��̃��[���h�s��
	//enemyPos		�G�l�~�[�̍��W
	void Init(IEnemy* enemy ,CVector3 enemyPos);

	//�X�V
	void Update();

	//�`��
	void Draw();

	//���W���擾
	const CVector3& GetPosition() const
	{
		return m_position;
	}

	//�ړ����x��ݒ�
	void SetMoveSpeed(const CVector3& moveSpeed)
	{
		m_characterController.SetMoveSpeed(moveSpeed);
	}

	//��𓊂��邩��ݒ�
	void SetIsThrow(bool isThrow)
	{
		m_isThrow = isThrow;
	}

private:
	CSkinModel				m_skinModel;			//�X�L�����f��
	CCharacterController	m_characterController;	//�L�����N�^�[�R���g���[���[
	CVector3				m_position;				//���W
	CQuaternion				m_rotation;				//��]
	CVector3				m_targetPos;			//�^�[�Q�b�g�̍��W
	const IEnemy*			m_enemy;				//�G�l�~�[
	CVector3				m_enemyPos;				//�G�̍��W
	const CMatrix*			m_enemyHandMatrix;		//�G�̎�̍s��
	bool					m_isThrow = false;		//��𓊂��邩
};