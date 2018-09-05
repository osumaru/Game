#pragma once

struct SplayerStatus
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

class CPlayer : public IGameObject
{

public:

	//�v���C���[�̏�����
	void Init(CVector3 position);

	//�v���C���[�̃C���X�^���X�̎擾
	static CPlayer& GetInstance()
	{
		static CPlayer player;
		return player;
	}

	//�v���C���[�̍X�V�֐�
	void Update()override;

	//�v���C���[�̕`��֐�
	void Draw()override;

	//�v���C���[�̍��W���擾����֐�
	const CVector3 GetPosition()
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
	const SplayerStatus& GetStatus()
	{
		return m_status;
	}

	//�v���C���[�̃��[���h�s����擾
	const CMatrix& GetWorldMatrix()
	{
		return m_skinmodel.GetWorldMatrix();
	}

	const int GetStrength()
	{
		return m_status.Strength;
	}

	//�v���C���[�̑����̕ύX���s������
	void WeaponChange();

	const CVector3 GetPlayerHead()
	{
		
		CMatrix PlayerHead = m_skinmodel.FindBoneWorldMatrix(L"Head");
		CVector3 PlayerHeadPos = { PlayerHead.m[3][0],PlayerHead.m[3][1],PlayerHead.m[3][2] };

		return PlayerHeadPos;
	}




private:
	CVector3				m_position;								//���W
	CVector3				m_moveSpeed = CVector3::Zero;			//�ړ����x
	CQuaternion				m_rotation = CQuaternion::Identity;		//��]
	CSkinModel				m_skinmodel;							//�X�L�����f��
	CCharacterController	m_characterController;					//�L�����N�^�[�R���g���[���[
	CPad					m_pad;									//�p�b�h
	CAnimation				m_animation;							//�A�j���[�V����
	SplayerStatus			m_status;								//�v���C���[�̃X�e�[�^�X
	bool					m_isSlip = false;						//�X���b�v����
	float					m_slipSpeed = 50.0f;					//����ړ����̃X�s�[�h

};

static CPlayer& GetPlayer()
{
	return CPlayer::GetInstance();
}