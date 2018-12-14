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
	//position	���W
	void Init(CVector3 position);
	//�X�V�����O�Ɉ�x�����Ă΂��
	bool Start();
	//�X�V
	void Update();
	//�`��
	void Draw();

private:
	CSkinModel				m_skinModel;			//�X�L�����f��
	CCharacterController	m_characterController;	//�L�����N�^�[�R���g���[���[
	CVector3				m_position;				//���W
	CQuaternion				m_rotation;				//��]
	CVector3				m_targetPos;			//�^�[�Q�b�g�̍��W
	CVector3				m_enemyPos;				//�G�̍��W
};