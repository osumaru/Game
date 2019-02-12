#pragma once
#include "../../Player/Weapon/WeaponCommon.h"
	//属性
	enum EnInventoryItemType {
		Recovery,	//回復
		Buff,		//バフ
		Equip,		//装備
		TypeNum,	//種類の数
		Invald		//何もない
	};
	//プレイヤーの何に影響を与えるのか
	enum EnIemEffectPlayerStatus
	{
		Strength,		//攻撃力
		Defense,		//守備力
		Health,			//体力
		None,			//効果なし
	};
	//アイテムのクオリティー
	enum EnItemQuality
	{
		enUnknown,
		enNormal,		//62%程度で手に入るアイテム
		enRare,			//30%程度で手に入るアイテム
		enLegend,		//8%程度で手に入るアイテム
		enSpecial,		//特定の場所以外では手に入らないもの
	};

	struct SItemStatus
	{
		wchar_t					ItemName[40];							//アイテムの名前
		wchar_t					ItemText[100];							//武器の説明
		wchar_t					ItemSprite[100];
		int						ItemID = 0;								//商品の番号
		int						Itemprice = 0;							//アイテムの値段
		int						ItemEffect = 0;							//効果値
		EnItemQuality			ItemQuality = EnItemQuality::enNormal;	//アイテムのクオリティー
		EnIemEffectPlayerStatus	ItemEffectPlayerStatus = EnIemEffectPlayerStatus::None;
		EnInventoryItemType		ItemType = Invald;						//そのアイテムが回復系なのか装備するものなのかを判別する
		EnPlayerWeapon			WeaponType = EnPlayerWeapon::enInvalid;	//装備の種類
	};