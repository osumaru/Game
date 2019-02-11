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

	//�X�V����O�Ɉ�x�����Ă΂��
	virtual bool Start() { return true; }

	//�X�V
	virtual void Update() = 0;

	//�`��
	virtual void Draw() {};

	//�����_���n�_�Ƀ|�b�v������
	//distance	�����_���n�_�܂ł̋���
	//upSpeed	�|�b�v�����������̑��x
	//�߂�l�@�ړ����x
	CVector3 RamdomPop(float distance, float upSpeed);

	//�A�C�e�����E�����Ƃ��ł��邩
	//isPopEnd	�|�b�v���I����Ă��邩
	//length	�A�C�e�����E���鋗��
	bool PickUp(bool isPopEnd, float length);

	//�ړ�
	//�߂�l�@�ړ����x
	CVector3 Move();

	//�����x�����Z�b�g����
	void AcceleReset()
	{
		m_accele = 0.0f;
	}
protected:
	CSkinModel				m_skinModel;				//�X�L�����f��
	CVector3				m_position;					//���W
	CQuaternion				m_rotation;					//��]
	CCharacterController	m_characterController;		//�L�����N�^�[�R���g���[���[
	const float				m_deadTime = 30.0f;			//�A�C�e�������ł���܂ł̎���
	float					m_timer = 0.0f;				//�^�C�}�[
	float					m_accele = 0.0f;			//�����x
	bool					m_isPopEnd = false;			//�|�b�v���I�������
	bool					m_isMove = false;			//�ړ����Ă��邩
};