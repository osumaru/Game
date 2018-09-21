/*
*	�A�C�e���N���X�̃C���^�[�t�F�[�X
*/

#pragma once

class IItem : public IGameObject
{
public:
	//�R���X�g���N�^
	IItem();

	//�f�X�g���N�^
	virtual ~IItem();

	//������
	//position	���W
	virtual void Init(CVector3 position) = 0;

	//�X�V
	virtual void Update() = 0;

	//�`��
	virtual void Draw() = 0;

protected:
	CSkinModel				m_skinModel;			//�X�L�����f��
	CVector3				m_position;				//���W
	CQuaternion				m_rotation;				//��]
	CCharacterController	m_characterController;	//�L�����N�^�[�R���g���[���[
	CVector3				m_popPosition;			//�A�C�e�����|�b�v������W
	CVector3				m_moveSpeed;			//�ړ����x
	const float				m_speed = 4.0f;			//���x
	float					m_timer = 0.0f;			//�^�C�}�[
	bool					m_popEnd = false;		//�|�b�v���I�������
};