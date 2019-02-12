#pragma once
#include "../../Player/Weapon/WeaponCommon.h"
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
		enUnknown,
		enNormal,		//62%���x�Ŏ�ɓ���A�C�e��
		enRare,			//30%���x�Ŏ�ɓ���A�C�e��
		enLegend,		//8%���x�Ŏ�ɓ���A�C�e��
		enSpecial,		//����̏ꏊ�ȊO�ł͎�ɓ���Ȃ�����
	};

	struct SItemStatus
	{
		wchar_t					ItemName[40];							//�A�C�e���̖��O
		wchar_t					ItemText[100];							//����̐���
		wchar_t					ItemSprite[100];
		int						ItemID = 0;								//���i�̔ԍ�
		int						Itemprice = 0;							//�A�C�e���̒l�i
		int						ItemEffect = 0;							//���ʒl
		EnItemQuality			ItemQuality = EnItemQuality::enNormal;	//�A�C�e���̃N�I���e�B�[
		EnIemEffectPlayerStatus	ItemEffectPlayerStatus = EnIemEffectPlayerStatus::None;
		EnInventoryItemType		ItemType = Invald;						//���̃A�C�e�����񕜌n�Ȃ̂�����������̂Ȃ̂��𔻕ʂ���
		EnPlayerWeapon			WeaponType = EnPlayerWeapon::enInvalid;	//�����̎��
	};