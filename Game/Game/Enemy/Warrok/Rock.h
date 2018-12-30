/*
*	�G���������N���X
*/

#pragma once

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
	void Init(const CMatrix* handMatrix, CVector3 enemyPos);

	//�X�V�����O�Ɉ�x�����Ă΂��
	bool Start();

	//�X�V
	void Update();

	//�`��
	void Draw();

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
	CVector3				m_enemyPos;				//�G�̍��W
	const CMatrix*			m_enemyHandMatrix;		//�G�̎�̍s��
	bool					m_isThrow = false;		//��𓊂��邩
};