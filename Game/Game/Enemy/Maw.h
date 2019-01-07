/*
*	�{�X�N���X
*/
#pragma once

class CBossHp;
class CWeekPoint;
struct SmawStatus {
	int Strength;			//�U����
	int Defense;			//�h���
	int	Hp;					//�̗�
	int MaxHp;				//�ő�̗�
	int Gold;				//�������z
};

class CMaw :
	public IGameObject
{
public:

	enum EnMawState {
		enState_Idle,			//�ҋ@
		enState_Walk,			//����
		enState_Attack,			//�U��
		enState_SpecialAttack,	//����U��
		enState_Damage,			//�_���[�W
		enState_Down,			//�_�E��
		enState_Death,			//���S
		enState_Num,			//��Ԃ̐�
		enState_Invald,			//�����Ȃ�
	};
	//�R���X�g���N�^
	CMaw();
	//�f�X�g���N�^
	~CMaw();

	//�v���C���[�̏�����
	void Init(const CVector3 position);

	//�v���C���[�̍X�V�֐�
	void Update()override;

	//�v���C���[�̕`��֐�
	void Draw()override;

	//���S����O�ɌĂ΂��֐�
	void BeforeDead() override;

	//�s���̑I��
	//void ActionStateOrder();

	//��]
	void Rotation();

	//��_�X�v���C�g�`��
	void WeekPointUpdate();

	//�ʏ�U��
	void Attack();

	//����U��
	void SpecialAttack();

	//�_�E�����
	void Down();

	//�v���C���[��T����]�Ȃǂ�
	void Search();

	//�ҋ@���
	void Idle();

	//���S
	void Death();

	//�A�j���[�V����
	bool Anim(EnMawState animState);

	//�C���X�^���X�̎擾
	static CMaw& GetInstance()
	{
		return *m_maw;
	}

	//�C���X�^���X�̐���
	static void CMaw::Create()
	{
		if (!m_maw)
		{
			m_maw = New<CMaw>(PRIORITY_ENEMY);
		}
	}

	//�C���X�^���X�̏���
	static void CMaw::Destroy()
	{
		Delete(m_maw);
		m_maw = nullptr;
	}

	//���W���擾
	const CVector3& GetPosition() const
	{
		return m_position;
	}

	//��_���W���擾
	const CVector3& GetWeekPosition() const
	{
		return m_weekPosition;
	}

	//�_���[�W������擾
	bool GetIsDamage()
	{
		return m_isDamage;
	}

	//�U��������擾
	bool GetIsAttack()
	{
		return m_isAttack;
	}

	//����������擾
	bool GetIsBattle()
	{
		return m_isBattle;
	}

	//�_�E����Ԃ��擾
	bool GetIsDown()
	{
		return m_isDown;
	}

	//�{�[���̃��[���h�s����擾
	const CMatrix& GetBoneMatrix(const wchar_t* boneName) const
	{
		return m_skinModel.FindBoneWorldMatrix(boneName);
	}
	//�X�e�[�^�X�̎擾
	const SmawStatus& GetSmawStatus() const
	{
		return m_status;
	}

	//�_���[�W�����ݒ�
	//isDamage	�_���[�W�t���O
	void SetIsDamage(bool isDamage);

	//����g�����U��
	void HandAttack(float DamageLength);

	//�A�j���[�V�����C�x���g���N�������ɌĂ΂�鏈���B
	//animClipName �A�j���[�V�����̃t�@�C���p�X
	//enentName		�A�j���[�V�����C�x���g��
	void OnInvokeAnimationEvent(const wchar_t* animClipName, const wchar_t* eventName);

	//���[���h�s��̎擾
	const CMatrix& GetWorldMatrix() const
	{
		return m_skinModel.GetWorldMatrix();
	}

private:
	//�s���p�^�[��
	enum EnMawActionPattern
	{
		enActionPatternAttack,			//�U��
		enActionPatternSpecialAttack,	//����U��
		enActionPatternIdle,			//�ҋ@
		enActionPatternSearch,			//�T��
		enActionPatternDown,			//�_�E��
		enActionPatternDeath,			//���S
		enActionPatternNum,				//��
	};

	static CMaw*			m_maw;										//�{�X
	CVector3				m_position;									//���W
	CQuaternion				m_rotation = CQuaternion::Identity;			//��]
	CVector3				m_scale = { 3.0f,3.0f, 3.0f };				//�g��
	CSkinModel				m_skinModel;								//�X�L�����f��
	CCharacterController	m_characterController;						//�L�����N�^�[�R���g���[���[
	CAnimation				m_animation;								//�A�j���[�V����
	SmawStatus				m_status;									//�X�e�[�^�X
	EnMawActionPattern		m_actionPattern;							//�s���p�^�[��
	CVector3				m_weekPosition;								//��_���W

	int						m_downCount = 0;							//����U�����󂯂���
	float					m_downTime=0.0f;							//�_�E�����Ă��鎞��
	float					m_damageInterval = 0.0f;					//�_���[�W�Ԋu

	bool					m_isAttack = false;							//�U������
	bool					m_isStand = false;							//�ҋ@����
	bool					m_isDamage = false;							//�_���[�W����
	bool					m_isDown = false;							//�_�E������
	bool					m_isDeath = false;							//���S����
	bool					m_isBattle = false;							//��������

	CBossHp*		m_bossHp = nullptr;			//�{�XHP
	CWeekPoint*		m_weekPoint = nullptr;		//�{�X�̎�_�X�v���C�g
};

//�{�X�̎擾
static CMaw& GetMaw()
{
	return CMaw::GetInstance();
}

