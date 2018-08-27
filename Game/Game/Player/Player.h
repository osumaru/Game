#pragma once

class Player : public GameObject
{
public:

	//�v���C���[�̏�����
	void Init(Vector3 position);

	//�v���C���[�̃C���X�^���X�̎擾
	static Player& GetInstance()
	{
		static Player player;
		return player;
	}

	//�v���C���[�̍X�V�֐�
	void Update()override;

	//�v���C���[�̕`��֐�
	void Draw()override;

	//�v���C���[�̍��W���擾����֐�
	Vector3 GetPosition()
	{
		return m_position;
	}

	//�v���C���[�̈ړ��������s���֐�
	void Move();

	//�v���C���[�̉�]���s���֐�
	void Rotation();

private:
	Vector3				m_position;							//���W
	Vector3				m_moveSpeed = Vector3::Zero;		//�ړ����x
	Quaternion			m_rotation = Quaternion::Identity;	//��]
	SkinModel			m_skinmodel;						//�X�L�����f��
	CharacterController m_characterController;				//�L�����N�^�[�R���g���[���[
	Pad					m_pad;			//�p�b�h
	Animation			animation;
};

static Player& GetPlayer()
{
	return Player::GetInstance();
}