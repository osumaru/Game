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
	virtual bool Use() { return false; }

	//�����_���n�_�Ƀ|�b�v������
	//distance	�����_���n�_�܂ł̋���
	//upSpeed	�|�b�v�����������̑��x
	virtual void RamdomPop(float distance, float upSpeed);

	//�A�C�e�����E�����Ƃ��ł��邩
	//isPopEnd	�|�b�v���I����Ă��邩
	//length	�A�C�e�����E���鋗��
	virtual bool PickUp(bool isPopEnd, float length);

	//����
	enum EnInventoryItemType {
		Recovery,	//��
		Buff,		//�o�t
		Equip,		//����
		TypeNum,	//��ނ̐�
		Invald		//�����Ȃ�
	};
	//�v���C���[�̉��ɉe����^����̂�
	enum EnIemEffectPlayerStatus
	{
		Strength,		//�U����
		Defense,		//�����
		Health,			//�̗�
		None,			//���ʂȂ�
	};
	//�����̏��A�C�e���̏ꍇ��NoWeapon
	enum EnWeaponType
	{
		enSword,			//�Ў茕
		enLongSword,		//���茕
		enArrow,			//�|��
		enTwinSword,		//��
		enNoWeapon,			//����ł͂Ȃ�
	};

	struct SItemStatus
	{
		wchar_t					ItemName[40];			//�A�C�e���̖��O
		int						ItemID = 0;				//���i�̔ԍ�
		int						Itemprice = 0;			//�A�C�e���̒l�i
		int						ItemEffect = 0;			//���ʒl
		EnIemEffectPlayerStatus	ItemEffectPlayerStatus = EnIemEffectPlayerStatus::None;
		EnInventoryItemType		ItemType = Invald;		//���̃A�C�e�����񕜌n�Ȃ̂�����������̂Ȃ̂��𔻕ʂ���
		EnWeaponType			WeaponType = enNoWeapon;
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
	const float				m_deadTime = 30.0f;			//�A�C�e�������ł���܂ł̎���
	float					m_timer = 0.0f;				//�^�C�}�[
};