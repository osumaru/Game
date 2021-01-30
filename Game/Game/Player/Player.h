#pragma once
#include "PlayerSate/PlayerStateMachine.h"
#include "PlayerSate/PlayerState.h"
#include "PlayerArrow.h"
#include "Weapon/WeaponManager.h"
#include "PlayerSate/PlayerStateCommon.h"
#include "WireAction.h"
#include "PlayerGetter.h"
#include "WireDraw.h"
#include "../Item/ItemList.h"
#include "../Item/EquipList.h"
class Command;
class IItem;

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
	CPlayer() { SetIsActive(false); }
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
			m_player = New<CPlayer>(PRIORITY_PLAYER);
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

	void AfterDraw()override;

	void BeforeDead()override;

	//�v���C���[�̍��W���擾����֐�
	const CVector3& GetPosition() const
	{
		return m_position;
	}

	//�v���C���[�̃X�e�[�^�X���擾
	const SplayerStatus& GetStatus() const
	{
		return m_status;
	}

	//������Ǘ�����N���X���擾
	CWeaponManager& GetWeaponManager()
	{
		return m_weaponManager;
	}

	//�v���C���[�̃X�L�����f���̏����擾
	const CSkinModel& GetSkinmodel() const
	{
		return m_skinmodel;
	}

	//�v���C���[�������Ă��邩�̔���
	bool GetIsDied() const
	{
		return m_isDied;
	}

	//�_���[�W���󂯂����̔���
	bool GetIsDamage() const
	{
		return m_isDamege;
	}

	//�L�����R�����擾
	const CCharacterController& GetCharacterController() const
	{
		return m_characterController;
	}

	//�X�e�[�^�X�̌v�Z�������s���֐�
	void StatusCalculation();

	/*�v���C���[�̌o���l�ʂ��グ��֐��i�Z�b�g����֐��ł͂Ȃ��ł��j
	�����œ|�����G�̌o���l�ʂ�����*/
	void ExpUP(const int expup)
	{
		if (expup <= 0) { return; }
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
		m_isStatusConversion = true;
	}

	//�v���C���[���������擾����
	//gold		����
	void GainGold(const int gold)
	{
		m_status.Gold += gold;
	}

	/*
	�v���C���[�̃_���[�W����
	DamageValue	�v���C���[�ɗ^����_���[�W��
	*/
	void SetDamage(int DamageValue)
	{
		if (!m_isDamege && !m_isInvinsible)
		{
			m_status.Health -= DamageValue;
			m_isDamege = true;
		}
	}

	//���������������̌v�Z���s��
	bool BuyMoney(const int buy)
	{
		if (m_status.Gold < buy) { return false; }
		m_status.Gold -= buy;
		return true;
	}

	//�X�e�[�^�X���ω����������擾
	const bool GetIsStatusConversion()
	{
		return m_isStatusConversion;
	}

	//�X�e�[�^�X���ω���������ݒ�
	void  SetIsStatusConversion(const bool iscon)
	{
		m_isStatusConversion = iscon;
	}

	//���C���[�A�N�V�������Ǘ�����N���X���擾
	CWireAction& GetWireAction()
	{
		return m_wireAction;
	}

	//�X�e�[�g�}�V�����擾�B
	CPlayerStateMachine& GetStateMachine()
	{
		return m_PlayerStateMachine;
	}

	//�_���[�W��^�����G�l�~�[�̍��W��ݒ�
	void SetDamageEnemyPos(const CVector3& position)
	{
		m_playerGetter.SetDamageEnemyPos(position);
	}

	//�X�^���U�����ǂ������擾
	bool GetStanAttack()
	{
		return m_isStanAttack;
	}

	//�X�^���U���ł��邩��ݒ�
	void SetStanAttack(bool isStanAttack)
	{
		m_isStanAttack = isStanAttack;
	}

	//�X�^���_���[�W�擾
	bool GetStanDamage()
	{
		return m_isStanDamage;
	}

	//�X�^���_���[�W�ݒ�
	void SetStanDamage(int StanDamageValue)
	{
		if (!m_isStanDamage && !m_isInvinsible)
		{
			m_status.Health -= StanDamageValue;
			m_isStanDamage = true;
		}
	}

	//�A�N�V���������邩���擾
	bool GetIsAction()
	{
		return m_isAction;
	}

	//�A�N�V���������邩��ݒ�
	//isAction		�A�N�V���������邩
	void SetIsAction(bool isAction)
	{
		m_isAction = isAction;
	}

	/*
	���̏�Ԃ֑J�ڂ��邽�߂̏����𖞂����Ă��邩�̃t���O��Ԃ��֐�
	state	�v���C���[�̃X�e�[�g
	ret		���
	*/
	bool GetIsStateCondition(CPlayerState::EnPlayerState state);

	//���̃{�[���̔ԍ����擾
	int GetSpineBoneID() const
	{
		return m_spineBoneID;
	}

	static CItemList& GetItemList()
	{
		return m_itemList;
	}

	static CEquipList& GetEquipList()
	{
		return m_equipList;
	}

	//�����R�}���h�̐ݒ�
	void SetCommand(Command* command)
	{
		if (m_command != nullptr)
		{
			delete m_command;
		}
		m_command = command;
	}

	//�x���R�}���h�̐ݒ�
	void SetDefferdCommand(Command* command)
	{

		if (m_defferdCommand != nullptr)
		{
			delete m_defferdCommand;
		}
		m_defferdCommand = command;
	}

	void ResetCommand()
	{
		if (m_command != nullptr)
		{
			delete m_command;
			m_command = nullptr;
		}
		if (m_defferdCommand != nullptr)
		{
			delete m_defferdCommand;
			m_defferdCommand = nullptr;
		}
	}
	friend class CPlayerGetter;
private:

	//�v���C���[�̉�]������֐�
	void Rotation(const CVector3& stickDir);

	//�A�j���[�V�����C�x���g���N�������ɌĂ΂�鏈���B
	void OnInvokeAnimationEvent(const wchar_t* animClipName, const wchar_t* eventName);
private:
	Command*							m_command = nullptr;					//�����R�}���h
	Command*							m_defferdCommand = nullptr;				//�x���R�}���h
	static CEquipList					m_equipList;
	static CItemList					m_itemList;								//�A�C�e�����X�g
	static CPlayer*						m_player;								//�v���C���[
	CPlayerGetter						m_playerGetter;							//�v���C���[�̃Q�b�^�[
	CVector3							m_position;								//���W
	CQuaternion							m_rotation = CQuaternion::Identity;		//��]
	CSkinModel							m_skinmodel;							//�X�L�����f��
	CCharacterController				m_characterController;					//�L�����N�^�[�R���g���[���[
	CAnimation							m_animation;							//�A�j���[�V����
	static SplayerStatus				m_status;								//�v���C���[�̃X�e�[�^�X
	CWeaponManager						m_weaponManager;						//����
	CPlayerStateMachine					m_PlayerStateMachine;					//�v���C���[�̃A�j���[�V�����̑J�ڂ��s���X�e�[�g�}�V�[��
	bool								m_isDamege = false;						//�_���[�W���󂯂Ă邩�̃t���O
	//bool								m_isAttack = false;						//�U�������̔���
	bool								m_isDied = false;						//����ł��邩�̔���
	bool								m_isStatusConversion = false;			//�X�e�[�^�X���ω��������𔻒肷��
	bool								m_isInvinsible = false;					//���G���̃t���O
	CWireAction							m_wireAction;							//���C���[�̔�Ԃ��ǂ����̔���������肷��Ƃ���
	CWireDraw							m_wireDraw;								//���C���[��`�悷��
	bool								m_isStanAttack = false;					//�X�^���U��
	bool								m_isStanDamage = false;					//�X�^���_���[�W
	CCollisionDetection					m_groundCollision;						//�n�ʗp�̃R���W����
	CBoxCollider						m_boxCollider;							//�{�b�N�X�R���C�_�[
	bool								m_isAction = true;						//�A�N�V���������邩�𔻒肷��
	const CMatrix*						m_hipBoneMat;							//���̃{�[���s��̃|�C���^
	CLight								m_light;
	int									m_spineBoneID;							//���̍���ID
};

static CPlayer& GetPlayer()
{
	return CPlayer::GetInstance();
}

static CItemList& GetItemList()
{
	return CPlayer::GetItemList();
}

static CEquipList& GetEquipList()
{
	return CPlayer::GetEquipList();
}