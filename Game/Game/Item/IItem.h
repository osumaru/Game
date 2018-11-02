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

	//�A�C�e�����g��
	virtual void Use() {};

	enum EnInventoryItemType {
		Recovery,	//��
		Buff,		//�o�t
		Equip,		//����
		TypeNum,	//��ނ̐�
		Invald		//�����Ȃ�
	};

	//�A�C�e���̎�ނ��擾
	EnInventoryItemType GetItemType()
	{
		return m_itemType;
	}

protected:
	EnInventoryItemType		m_itemType = Invald;		//�C���x���g���̃A�C�e���̎��
	CSkinModel				m_skinModel;				//�X�L�����f��
	CVector3				m_position;					//���W
	CQuaternion				m_rotation;					//��]
	CCharacterController	m_characterController;		//�L�����N�^�[�R���g���[���[
	CVector3				m_popPosition;				//�A�C�e�����|�b�v������W
	CVector3				m_moveSpeed;				//�ړ����x
	const float				m_speed = 4.0f;				//���x
	float					m_timer = 0.0f;				//�^�C�}�[
	bool					m_popEnd = false;			//�|�b�v���I�������
};