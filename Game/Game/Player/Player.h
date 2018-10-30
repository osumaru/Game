#pragma once
#include "PlayerSate/PlayerStateMachine.h"
#include "PlayerSate/PlayerState.h"
#include "PlayerArrow.h"
#include "Weapon.h"
#include "PlayerSate/PlayerStateCommon.h"

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

	//�v���C���[�̏�����
	void Init(CVector3 position);

	//�v���C���[�̃C���X�^���X�̎擾
	static CPlayer& GetInstance()
	{
		return *m_player;
	}

	//�C���X�^���X�̐���
	static void CPlayer::Create()
	{
		if (!m_player)
		{
			m_player = New<CPlayer>(1);
		}
	}

	//�C���X�^���X�̏���
	static void CPlayer::Destroy()
	{
		Delete(m_player);
		m_player = nullptr;
	}

	//�v���C���[�̍X�V�֐�
	void Update()override;

	//�v���C���[�̕`��֐�
	void Draw()override;

	//�v���C���[�̍��W���擾����֐�
	const CVector3& GetPosition() const
	{
		return m_position;
	}
	//�v���C���[�̍��W��ݒ肷��֐�
	void SetPosition(const CVector3 setpos)
	{
		 m_characterController.SetPosition(setpos);
	}
	//�v���C���[�̉�]�����擾
	const CQuaternion& GetPlayerrRot()
	{
		return m_rotation;
	}

	//�A�j���[�V�����̏����擾
	const CAnimation& GetAnimation() const
	{
		return m_animation;
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
	void SetPlayerAnimation(EnPlayerAnimation animNumber, const float num)
	{
		m_animation.Play(animNumber, num);
		m_State = animNumber;
	}

	//�v���C���[�̃X�e�[�^�X���擾
	const SplayerStatus& GetStatus() const
	{
		return m_status;
	}

	//�v���C���[�̃��[���h�s����擾
	const CMatrix& GetWorldMatrix() const
	{
		return m_skinmodel.GetWorldMatrix();
	}

	//�v���C���[�̃X�s�[�h���擾����
	const CVector3& GetMoveSpeed() const
	{
		return m_characterController.GetMoveSpeed();
	}

	//�v���C���[�̓��̃{�[���̈ʒu���擾
	CVector3 GetPlayerHead() const
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
	bool GetIsDied() const
	{
		return m_isDied;
	}

	//���S��������ݒ�
	void SetIsDeid(bool SetDied)
	{
		m_isDied = SetDied;
	}

	//�_���[�W���󂯂����̔���
	bool GetIsDamage() const
	{
		return m_isDamege;
	}

	//�_���[�W���󂯂����̐ݒ�
	void SetIsDamage(bool SetDamage)
	{
		m_isDamege = SetDamage;
	}
	//�U���������擾
	bool GetIsAttack() const
	{
		return m_isAttack;
	}

	//�U�����������̐ݒ�
	void SetAttack(bool SetA)
	{
		m_isAttack = SetA;
	}

	//�X�e�[�g�}�V�[���̂���Ƃ�
	CPlayerStateMachine& GetPlayerStateMachine()
	{
		return m_PlayerStateMachine;
	}

	void SetMoveSpeed(const CVector3& moveSpeed)
	{
		m_characterController.SetMoveSpeed(moveSpeed);
	}

	const CWeapon& GetWeapon() const
	{
		return m_weapon;
	}
	
	//�v���C���[�̃X�L�����f���̏����擾
	const CSkinModel& GetPlayerSkin() const
	{
		return m_skinmodel;
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

	const CCharacterController& GetCharacterController() const
	{
		return m_characterController;
	}

	//���C���[�ړ����Ă��邩
	bool IsWireMove()
	{
		return m_isWireMove;
	}
	

	//���C���[�ړ����Ă��邩��ݒ�
	void SetIsWireMove(bool isWireMove)
	{
		m_isWireMove = isWireMove;
	}

	//��𐶐����Ă��邩�̐ݒ�
	void SetInitArrow(const bool set)
	{
		m_initArrow = set;
	}


	void SetAnimationPlay(EnPlayerAnimation state, float interporationTime)
	{
		m_animation.Play(state, interporationTime);
	}

	void SetAnimationPlay(EnPlayerAnimation state)
	{
		m_animation.Play(state);
	}

	//�|�𐶐�����֐�
	void InitArrow();
private:
	void PlayerMove();

	void Rotation();

	//�A�j���[�V�����C�x���g���N�������ɌĂ΂�鏈���B
	void OnInvokeAnimationEvent(const wchar_t* animClipName, const wchar_t* eventName);
private:
	static CPlayer*				m_player;								//�v���C���[
	CWeapon					m_weapon;
	CVector3				m_position;									//���W
	CQuaternion				m_rotation = CQuaternion::Identity;			//��]
	CSkinModel				m_skinmodel;								//�X�L�����f��
	CCharacterController	m_characterController;						//�L�����N�^�[�R���g���[���[
	CAnimation				m_animation;								//�A�j���[�V����
	SplayerStatus			m_status;									//�v���C���[�̃X�e�[�^�X
	bool					m_isSlip = false;							//�X���b�v����
	float					m_slipSpeed = 2.0f;							//����ړ����̃X�s�[�h
	EnPlayerAnimation		m_State = enPlayerAnimationStand;			//�A�j���[�V������J�ڂ����邽�߂̕ϐ�
	const float				INTERVAL = 1.5;								//�_���[�W���󂯂���̖��G����
	bool					m_isDamege = false;
	float					m_animetionFrame = 0.0f;
	bool					m_isAttack = false;							//�U�������̔���
	bool					m_isDied = false;							//����ł��邩�̔���
	bool					m_intervalOn = false;						//���G�����̔���
	bool					m_initArrow = false;						//�|�𐶐����Ă��邩�̔���
	float					m_intervalTime = 0.0f;

	CPlayerStateMachine			m_PlayerStateMachine;							//�v���C���[�̃A�j���[�V�����̑J�ڂ��s���X�e�[�g�}�V�[��
	std::list<CPlayerArrow*>	m_arrowList;									//�|��̃��X�g
	CSprite						m_arrowtag;										//�T�[�N���̃X�v���C�g
	CTexture					m_arrowtexture;
	bool						m_isZoom;										//�|�p�̎��_�ɐ؂�ւ��邩�̔��������ϐ�

	bool					m_isWireMove = false;					//���C���[�ړ��ł��邩
	CRayTest				m_wireCollisionSolver;					//���C���[�ړ��̃R���W���������N���X
	CVector3				m_wirePosition;							//���C���[�ړ���̍��W
};

static CPlayer& GetPlayer()
{
	return CPlayer::GetInstance();
}