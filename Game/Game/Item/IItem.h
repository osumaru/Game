/*
*	�A�C�e���N���X�̃C���^�[�t�F�[�X
*/

#pragma once
#include "../Player/Weapon/WeaponCommon.h"
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

	//�����_���n�_�Ƀ|�b�v������
	//distance	�����_���n�_�܂ł̋���
	//upSpeed	�|�b�v�����������̑��x
	virtual void RamdomPop(float distance, float upSpeed);

	//�A�C�e�����E�����Ƃ��ł��邩
	//isPopEnd	�|�b�v���I����Ă��邩
	//length	�A�C�e�����E���鋗��
	virtual bool PickUp(bool isPopEnd, float length);

	//�ړ�
	virtual CVector3 Move();

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
	//�A�C�e���̃N�I���e�B�[
	enum EnItemQuality
	{
		enNormal,
		enRare,
		enLegend,
	};

	struct SItemStatus
	{
		wchar_t					ItemName[40];							//�A�C�e���̖��O
		wchar_t					ItemText[100];							//����̐���
		int						ItemID = 0;								//���i�̔ԍ�
		int						Itemprice = 0;							//�A�C�e���̒l�i
		int						ItemEffect = 0;							//���ʒl
		EnItemQuality			ItemQuality = EnItemQuality::enNormal;	//�A�C�e���̃N�I���e�B�[
		EnIemEffectPlayerStatus	ItemEffectPlayerStatus = EnIemEffectPlayerStatus::None;
		EnInventoryItemType		ItemType = Invald;						//���̃A�C�e�����񕜌n�Ȃ̂�����������̂Ȃ̂��𔻕ʂ���
		EnPlayerWeapon			WeaponType = EnPlayerWeapon::enInvalid;	//�����̎��
	};


protected:
	CSkinModel				m_skinModel;				//�X�L�����f��
	CVector3				m_position;					//���W
	CQuaternion				m_rotation;					//��]
	CCharacterController	m_characterController;		//�L�����N�^�[�R���g���[���[
	const float				m_deadTime = 30.0f;			//�A�C�e�������ł���܂ł̎���
	float					m_timer = 0.0f;				//�^�C�}�[
	float					m_accele = 0.0f;
	bool					m_isPopEnd = false;			//�|�b�v���I�������
	bool					m_isMove = false;
};