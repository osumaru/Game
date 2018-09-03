#pragma once

struct playerStatus
{
	int Strength;			//�U����
	int Defense;			//�h���
	int	Health;				//�̗�
	int Level;				//���x��
	int ExperiencePoint	;	//���݂̌o���l
	int NextExp;			//���x���A�b�v�܂łɕK�v�Ȍo���l
	int OldExp;				//���݂̃��x���A�b�v�ɕK�v�������o���l
	int AccumulationExp;	//�ݐόo���l

};

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
	const Vector3 GetPosition()
	{
		return m_position;
	}

	//�v���C���[�̈ړ��������s���֐�
	void Move();

	//�v���C���[�̉�]���s���֐�
	void Rotation();

	//�v���C���[�̃A�j���[�V�����̏������s���֐�
	void AnimationMove();

	//�X�e�[�^�X�̌v�Z�������s���֐�
	void StatusCalculation();

	//�v���C���[�̌o���l�ʂ��グ��֐��i�Z�b�g����֐��ł͂Ȃ��ł��j
	//�����œ|�����G�̌o���l�ʂ�����
	void ExpUP(const int expup)
	{
		m_status.ExperiencePoint += expup;
		m_status.AccumulationExp += expup;
	}

	//�v���C���[�̃X�e�[�^�X���擾
	const playerStatus& GetStatus()
	{
		return m_status;
	}


	const int GetStrength()
	{
		return m_status.Strength;
	}

	//�v���C���[�̑����̕ύX���s������
	void WeaponChange();


private:
	Vector3				m_position;							//���W
	Vector3				m_moveSpeed = Vector3::Zero;		//�ړ����x
	Quaternion			m_rotation = Quaternion::Identity;	//��]
	SkinModel			m_skinmodel;						//�X�L�����f��
	CharacterController m_characterController;				//�L�����N�^�[�R���g���[���[
	Pad					m_pad;								//�p�b�h
	Animation			m_animation;						//�A�j���[�V����
	playerStatus		m_status;							//�v���C���[�̃X�e�[�^�X
	bool				m_isSlip = false;					//�X���b�v����
	float				m_slipSpeed = 8.0f;

};

static Player& GetPlayer()
{
	return Player::GetInstance();
}