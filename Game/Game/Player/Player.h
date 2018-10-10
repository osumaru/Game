#pragma once
#include "PlayerSate/PlayerStateMachine.h"
#include "PlayerSate/PlayerState.h"
#include "PlayerRotation.h"
#include "PlayerMove.h"
#include "PlayerArrow.h"
#include "WireCollisionSolver.h"

struct SplayerStatus
{
	int Strength;			//�U����
	int Defense;			//�h���
	int	Health;				//�̗�
	int MaxHealth;			//���x�����Ƃ̍ő�HP
	int Level;				//���x��
	int ExperiencePoint	;	//���݂̌o���l
	int NextExp;			//���x���A�b�v�܂łɕK�v�Ȍo���l
	int OldExp;				//���݂̃��x���A�b�v�ɕK�v�������o���l
	int AccumulationExp;	//�ݐόo���l
	int Gold;

};

class CPlayer : public IGameObject
{

public:
	enum EnPlayerAnimeState
	{
		enPlayerStand,		//�ҋ@�A�j���[�V����
		enPlayerWalk,		//���s�A�j���[�V����
		enPlayerRun,		//����A�j���[�V����
		enPlayerRunJump,	//����W�����v
		enPlayerJump,		//�W�����v�A�j���[�V����
		enPlayerAttack,		//�U���A�j���[�V����
		enPlayerAttack2,	//�A���A�j���[�V����
		enPlayerDamage,		//�_���[�W�A�j���[�V����
		enPlayerAvoidance,	//����A�j���[�V����

		enPlayerDete,		//���S�A�j���[�V����
		enPlayerArroAttack,	//�|�̃A�j���[�V����
		enPlayerLongSwordAttack,//�匕�̍U���A�j���[�V����
		enPlayerTwinSwordAttack,//�񓁗��̍U���A�j���[�V����
		enPlayerNum			//�A�j���[�V�����̐�

	};

	enum EnPlayerWeapon
	{
		enSword,			//�Ў茕
		enLongSword,		//���茕
		enArro,				//�|��
		enTwinSword,		//��

	};

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
	//�v���C���[�̍��W��ݒ肷��֐�
	void SetPosition(const CVector3 setpos)
	{
		 m_position = setpos;
	}
	//�v���C���[�̉�]�����擾
	const CQuaternion& GetPlayerrRot()
	{
		return m_rotation;
	}
	//�v���C���[�̉�]�̐ݒ�
	void SetPlayerRot(const CQuaternion Setrot)
	{
		m_rotation = Setrot;
	}
	//�A�j���[�V�����̏����擾
	const CAnimation& GetAnimation()
	{
		return m_animation;
	}
	CCharacterController& GetCharacterController()
	{
		return m_characterController;
	}

	//�X�e�[�^�X�̌v�Z�������s���֐�
	void StatusCalculation();

	/*�v���C���[�̌o���l�ʂ��グ��֐��i�Z�b�g����֐��ł͂Ȃ��ł��j
	�����œ|�����G�̌o���l�ʂ�����*/
	void ExpUP(const int expup)
	{
		m_status.ExperiencePoint += expup;
		m_status.AccumulationExp += expup;
	}

	//�v���C���[��HP�񕜂�����
	//recoveryValue		�񕜒l
	void RecoveryHP(const int recoveryValue)
	{
		m_status.Health += recoveryValue;
		if (m_status.Health >= m_status.MaxHealth) {
			m_status.Health = m_status.MaxHealth;
		}
	}

	//�v���C���[���������擾����
	//gold		����
	void GainGold(const int gold)
	{
		m_status.Gold += gold;
	}

	/*�A�j���[�V�����̐ݒ�
	�������@�A�j���[���[�V�����̔ԍ��@�������@�⊮����*/
	void SetPlayerAnimation(const int animNumber, const float num)
	{
		m_animation.Play(animNumber, num);
		m_State = (EnPlayerAnimeState)animNumber;
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

	//�v���C���[�̃X�s�[�h���擾����
	const CVector3& GetMoveSpeed()
	{
		return m_moveSpeed;
	}

	//�v���C���[�̃X�s�[�h�̐ݒ�
	void SetMoveSpeed(const CVector3 setmovespeed)
	{
		m_moveSpeed = setmovespeed;
	}
	//�v���C���[�̑����̕ύX���s������
	void WeaponChange();

	//�v���C���[�̓��̃{�[���̈ʒu���擾
	const CVector3 GetPlayerHead()
	{
		
		CMatrix PlayerHead = m_skinmodel.FindBoneWorldMatrix(L"Head");
		CVector3 PlayerHeadPos = { PlayerHead.m[3][0],PlayerHead.m[3][1],PlayerHead.m[3][2] };

		return PlayerHeadPos;
	}

	void PlayerAttack();
	//�v���C���[�̃_���[�W����
	void GetDamage()
	{
		if (!m_isDamege && !m_intervalOn)
		{
			m_status.Health -= 5;
			m_isDamege = true;
		}
	}
	//�v���C���[�������Ă��邩�̔���
	bool GetIsDied()
	{
		return m_isDied;
	}
	//���S��������ݒ�
	void SetIsDeid(const bool SetDied)
	{
		m_isDied = SetDied;
	}
	//
	//�_���[�W���󂯂����̔���
	bool GetIsDamage()
	{
		return m_isDamege;
	}
	//�_���[�W���󂯂����̐ݒ�
	void SetIsDamage(const bool SetDamage)
	{
		m_isDamege = SetDamage;
	}
	//�U���������擾
	bool GetIsAttack()
	{
		return m_isAttack;
	}

	//�U�����������̐ݒ�
	void SetAttack(const bool SetA)
	{
		m_isAttack = SetA;
	}
	//����̍��̂̎擾
	CRigidBody& GetWeaponBody()
	{
		return m_weaponRigitBody;
	}
	//�X�e�[�g�}�V�[���̂���Ƃ�
	CPlayerStateMachine& GetPlayerStateMachine()
	{
		return m_PlayerStateMachine;
	}
	//����̐؂�ւ���ݒ肷��֐�
	void SetChangeWeapon(const int changeWeapon)
	{
		m_weaponState = (EnPlayerWeapon)changeWeapon;
		
	}
	//����̍��W�̐ݒ�
	void SetWeaponPosition(const CVector3 swpos)
	{
		m_weaponPosition =  swpos;
	}
	//����̍��W���擾
	const CVector3 GetWeaponPosition()
	{
		return m_weaponPosition;
	}
	//����̌����̐ݒ�
	void SetWeaponRotation(const CQuaternion setrot)
	{
		m_weaponRotation = setrot;
	}
	
	//�v���C���[�̃X�L�����f���̏����擾
	CSkinModel& GetPlayerSkin()
	{
		return m_skinmodel;
	}
	//�v���C���[�������Ă��邩���擾
	const bool GetIsGround()
	{	
		return m_isGround;
	}
	//���G���Ԃ�ݒ肷��
	void SetInterval(const bool set)
	{
		m_intervalOn = set;
	}

	//���C���[�ړ������̍��W���擾
	const CVector3& GetWirePosition()
	{
		return m_wirePosition;
	}

	//���C���[�ړ��ł��邩���擾
	bool IsWireMove()
	{
		return m_isWireMove;
	}

	const CSkinModel& GetWeaponskin(int num)
	{
		return m_weaponskin[num];
	}
	 
	const CVector3 GetTargetPos()
	{
		return m_cameraTargetPos;
	}

	void SetTargetPos(const CVector3 settar)
	{
		m_cameraTargetPos = settar;
	}

private:
	

	CVector3				m_position;										//���W
	CVector3				m_weaponPosition;								//����̍��W
	CVector3				m_moveSpeed = CVector3::Zero;					//�ړ����x
	CVector3				m_weaponScale = CVector3::One;
	CVector3				m_cameraTargetPos = CVector3::Zero;

	CQuaternion				m_rotation = CQuaternion::Identity;				//��]
	CQuaternion				m_weaponRotation = CQuaternion::Identity;		//����̉�]
	CSkinModel				m_skinmodel;									//�X�L�����f��
	CSkinModel				m_weaponskin[4];								//����̃X�L�����f��
	CCharacterController	m_characterController;							//�L�����N�^�[�R���g���[���[
	CLight					m_light;										//���C�g
	CBoxCollider			m_weaponBoxCollider;								//����p�̃{�b�N�X�R���C�_�[
	CRigidBody				m_weaponRigitBody;								//�{�b�N�X�p��rigidBody

	CPad					m_pad;									//�p�b�h
	CAnimation				m_animation;							//�A�j���[�V����
	SplayerStatus			m_status;								//�v���C���[�̃X�e�[�^�X
	bool					m_isSlip = false;						//�X���b�v����
	float					m_slipSpeed = 2.0f;						//����ړ����̃X�s�[�h
	EnPlayerAnimeState		m_State = enPlayerStand;				//�A�j���[�V������J�ڂ����邽�߂̕ϐ�
	EnPlayerWeapon			m_weaponState = EnPlayerWeapon::enSword;

	const float				RUN_SPEED	= 1.4f;				
	const float				WALK_SPEED	= 300.0f;
	const float				INTERVAL = 1.5;								//�_���[�W���󂯂���̖��G����
	bool					m_isDamege = false;
	float					m_animetionFrame = 0.0f;
	bool					m_isAttack = false;
	bool					m_isDied = false;
	bool					m_isGround = false;
	bool					m_intervalOn = false;
	float					m_intervalTime = 0.0f;

	CPlayerStateMachine			m_PlayerStateMachine;							//�v���C���[�̃A�j���[�V�����̑J�ڂ��s���X�e�[�g�}�V�[��
	CPlayerRotation				m_PlayerRotation;								//�v���C���[�̉�]�������N���X
	CPlayerMove					m_PlayerMove;									//�v���C���[�̓����������N���X
	std::list<CPlayerArrow*>	m_arrowList;									//�|��̃��X�g

	bool					m_isWireMove = false;					//���C���[�ړ��ł��邩
	CWireCollisionSolver	m_wireCollisionSolver;					//���C���[�ړ��̃R���W���������N���X
	CVector3				m_wirePosition;							//���C���[�ړ���̍��W
};

static CPlayer& GetPlayer()
{
	return CPlayer::GetInstance();
}