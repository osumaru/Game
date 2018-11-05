/*
*	�{�X�N���X
*/
#pragma once

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
		enState_Idle,	//�ҋ@
		enState_Walk,	//����
		enState_Attack,	//�U��
		enState_Damage,	//�_���[�W
		enState_Death,	//���S
		enState_Num,	//��Ԃ̐�
		enState_Invald,	//�����Ȃ�
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

	//�s���̑I��
	void ActionStateOrder();

	//�ʏ�U��
	void Attack();

	//����U��
	void SpecialAttack();

	//�_�E�����
	void Down();

	//�v���C���[��T����]�Ȃǂ�
	void Find();

	//�ҋ@���
	void Stand();

	//���S
	void Death();

	//�v���C���[�̃C���X�^���X�̎擾
	static CMaw& GetInstance()
	{
		return *m_maw;
	}

	//�C���X�^���X�̐���
	static void CMaw::Create()
	{
		if (!m_maw)
		{
			m_maw = New<CMaw>(1);
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

	//����I�u�W�F�N�g�ɓ�����������
	bool GetBreakObjectHit()
	{
		return m_isBreakObjectHit;
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

	//���[���h�s����擾
	const CVector3& GetLeftHandBone() const
	{
		CMatrix MawHand = m_skinModel.FindBoneWorldMatrix(L"LeftHand");
		CVector3 LeftHandPos = { MawHand.m[3][0],MawHand.m[3][1] ,MawHand.m[3][2] };
		return LeftHandPos;
	}

	//�_���[�W�����ݒ�
	//isDamage	�_���[�W�t���O
	void SetIsDamage(bool isDamage);


	////HP�����炷
	////damage	�_���[�W
	//void HpDamage(int damage)
	//{
	//	m_status.Hp -= damage;
	//}

	//�A�j���[�V�����C�x���g���N�������ɌĂ΂�鏈���B
	//animClipName �A�j���[�V�����̃t�@�C���p�X
	//enentName		�A�j���[�V�����C�x���g��
	void OnInvokeAnimationEvent(const wchar_t* animClipName, const wchar_t* eventName);

private:
	//�s���p�^�[��
	enum EnMawActionPattern
	{
		enActionPatternAttack,			//�U��
		enActionPatternSpecialAttack,	//����U��
		enActionPatternStand,			//�ҋ@
		enActionPatternFind,			//�T��
		enActionPatternDown,			//�_�E��
		enActionPatternDeath,			//���S
		enActionPatternNum,				//��
	};

	static CMaw*			m_maw;										//�{�X
	CVector3				m_position;									//���W
	CQuaternion				m_rotation = CQuaternion::Identity;			//��]
	CVector3				m_scale = { 10.0f,10.0f, 10.0f };			//�g��
	CSkinModel				m_skinModel;								//�X�L�����f��
	CCharacterController	m_characterController;						//�L�����N�^�[�R���g���[���[
	CAnimation				m_animation;								//�A�j���[�V����
	SmawStatus				m_status;									//�X�e�[�^�X
	EnMawActionPattern		m_actionPattern;							//�s���p�^�[��

	int						m_downCount = 0;							//����U�����󂯂���
	const int				m_attackPattern = 2;						//�U���̎�ނ̐�
	float					m_downTime=0.0f;							//�_�E�����Ă��鎞��
	float					m_damageInterval = 0.0f;					//�_���[�W�Ԋu

	bool					m_isAttack=false;							//�U������
	bool					m_isSpecialAttack = false;					//����U������
	bool					m_isBreakObjectHit = false;					//����I�u�W�F�N�g�ɓ����������ǂ���
	bool					m_isStand = false;							//�ҋ@����
	bool					m_isDamage = false;							//�_���[�W����
	bool					m_isDown = false;							//�_�E������
	bool					m_isDeath = false;							//���S����


	/////AnimationEvent������܂ł̍U������p
	float m_attackTime=0.0f;											//�U������
};

//�{�X�̎擾
static CMaw& GetMaw()
{
	return CMaw::GetInstance();
}

