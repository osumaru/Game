#pragma once
#include "PlayerSate/PlayerStateMachine.h"
#include "PlayerSate/PlayerState.h"
#include "PlayerArrow.h"
#include "Weapon.h"
#include "PlayerSate/PlayerStateCommon.h"
#include "WireAction.h"
#include "PlayerGetter.h"
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

	void AfterDraw();

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
	const CWeapon& GetWeapon() const
	{
		return m_weapon;
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

	//�U���������擾
	bool GetIsAttack() const
	{
		return m_isAttack;
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

	//�����A�C�e�����X�g�ɒǉ�
	//item		�A�C�e�����X�g�ɒǉ�����A�C�e��
	void AddItemList(IItem* item);

	//�����������X�g�ɒǉ�
	//item		�������X�g�ɒǉ�����A�C�e��
	void AddEquipList(CWeapon::SWeaponStatus item);

	//�����A�C�e�����X�g���擾
	std::list<IItem*> GetItemList()
	{
		return m_itemList;
	}

	//�����������X�g���擾
	std::list<CWeapon::SWeaponStatus> GetEquipList()
	{
		return m_equipList;
	}

	//�����A�C�e�����g��
	//number		�A�C�e���̔ԍ�
	void UseItem(int number);

	//�����̕ύX
	//number		�ύX�����������̔ԍ�
	void ChangeEquip(int number);

	//���������������̌v�Z���s��
	bool BuyMoney(const int buy)
	{
		if (m_status.Gold < buy) { return false; }
		m_status.Gold -= buy;
		return true;
	}

	//�|�𐶐�����֐�
	void InitArrow();

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

	/*
	����̃X�e�[�^�X���擾
	weaponNum	����̎��
	*/
	CWeapon::SWeaponStatus GetWeaponStatus(CWeapon::EnPlayerWeapon weaponNum)
	{
		return m_equipWeapon[weaponNum];
	}

	friend class CPlayerGetter;
private:

	//�v���C���[�̉�]������֐�
	void Rotation();

	//�A�j���[�V�����C�x���g���N�������ɌĂ΂�鏈���B
	void OnInvokeAnimationEvent(const wchar_t* animClipName, const wchar_t* eventName);
private:
	static CPlayer*						m_player;								//�v���C���[
	CPlayerGetter						m_playerGetter;							//�v���C���[�̃Q�b�^�[
	CVector3							m_position;								//���W
	CQuaternion							m_rotation = CQuaternion::Identity;		//��]
	CSkinModel							m_skinmodel;							//�X�L�����f��
	CCharacterController				m_characterController;					//�L�����N�^�[�R���g���[���[
	CAnimation							m_animation;							//�A�j���[�V����
	SplayerStatus						m_status;								//�v���C���[�̃X�e�[�^�X
	CWeapon								m_weapon;								//����
	CPlayerStateMachine					m_PlayerStateMachine;					//�v���C���[�̃A�j���[�V�����̑J�ڂ��s���X�e�[�g�}�V�[��
	bool								m_isDamege = false;						//�_���[�W���󂯂Ă邩�̃t���O
	bool								m_isAttack = false;						//�U�������̔���
	bool								m_isDied = false;						//����ł��邩�̔���
	bool								m_isStatusConversion = false;			//�X�e�[�^�X���ω��������𔻒肷��
	bool								m_isInvinsible = false;					//���G���̃t���O

	std::list<CPlayerArrow*>			m_arrowList;							//�|��̃��X�g
	CSprite								m_arrowtag;								//�T�[�N���̃X�v���C�g
	CTexture							m_arrowtexture;
	bool								m_isZoom;								//�|�p�̎��_�ɐ؂�ւ��邩�̔��������ϐ�

	std::list<IItem*>					m_itemList;								//�����A�C�e���̃��X�g
	std::list<CWeapon::SWeaponStatus>	m_equipList;							//���������̃��X�g
	CWeapon::SWeaponStatus				m_equipWeapon[CWeapon::enWeaponNum];	//�������̕���
	CWireAction							m_wireAction;							//���C���[�̔�Ԃ��ǂ����̔���������肷��Ƃ���
};

static CPlayer& GetPlayer()
{
	return CPlayer::GetInstance();
}