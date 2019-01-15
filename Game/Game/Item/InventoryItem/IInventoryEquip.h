#pragma once

#include "../../Player/Weapon/WeaponCommon.h"

class IInventoryEquip 
{
public:
	//コンストラクタ
	IInventoryEquip() {};

	//デストラクタ
	virtual ~IInventoryEquip() {};

	//初期化
	virtual void Init(const wchar_t* itemName, const wchar_t* textureFileName) {};

	//描画
	virtual void Draw() {};

	//アイテムのスプライトを取得
	CSprite* GetSprite()
	{
		return &m_itemSprite;
	}

	//アイテムの名前を取得
	const wchar_t* GetItemName() const
	{
		return m_itemName;
	}

	//テクスチャファイルの名前を取得
	const wchar_t* GetTextureFileName() const
	{
		return m_textureFileName;
	}

	//装備のステータスを設定
	void SetEquipStatus(SWeaponStatus equipStatus)
	{
		m_equipStatus = equipStatus;
	}

	//装備のステータスを取得
	SWeaponStatus GetEquipStatus()
	{
		return m_equipStatus;
	}

protected:
	CSprite					m_itemSprite;			//アイテムのスプライト
	const wchar_t*			m_itemName;				//アイテムの名前
	const wchar_t*			m_textureFileName;		//テクスチャファイルの名前
	SWeaponStatus			m_equipStatus;			//装備のステータス
};