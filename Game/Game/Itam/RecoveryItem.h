/*
*	�񕜃A�C�e���N���X
*/

#pragma once

class CRecoveryItem : public IGameObject
{
public:
	//������
	//position	���W
	void Init(CVector3 position);

	//�X�V����O�Ɉ�x�����Ă΂��
	bool Start();

	//�X�V
	void Update();

	//�`��
	void Draw();

	//�ړ�
	void Move();

private:
	CSkinModel				m_skinModel;			//�X�L�����f��
	CVector3				m_position;				//���W
	CQuaternion				m_rotation;				//��]
	CCharacterController	m_characterController;	//�L�����N�^�[�R���g���[���[
	CVector3				m_popPosition;			//�A�C�e�����|�b�v������W
	float					m_speed = 4.0f;			//�ړ����x
};
