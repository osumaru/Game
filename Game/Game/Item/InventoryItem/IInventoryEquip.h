#pragma once

#include "../../Player/Weapon/WeaponCommon.h"
#include "../GameItem/ItemStatus.h"

class IInventoryEquip 
{
public:
	//コンストラクタ
	IInventoryEquip() {};

	//デストラクタ
	virtual ~IInventoryEquip() {};

	//初期化
	//itemName			アイテムの名前
	//textureFilePath	テクスチャのファイルパス
	virtual void Init(const wchar_t* itemName, const wchar_t* textureFilePath) {};

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

	//テクスチャのファイルパスを取得
	const wchar_t* GetTextureFilePath() const
	{
		return m_textureFilePath;
	}

	//装備のステータスを設定
	//equipStatus	装備ステータス
	void SetEquipStatus(SWeaponStatus equipStatus)
	{
		m_equipStatus = equipStatus;
	}

	//装備のステータスを取得
	SWeaponStatus GetEquipStatus()
	{
		return m_equipStatus;
	}

	//アイテムのステータスを設定
	void SetItemStatus(const SItemStatus& status)
	{
		m_status = status;
	}

	//アイテムのステータスを取得
	SItemStatus& GetItemStatus()
	{
		return m_status;
	}

protected:
	SItemStatus				m_status;
	CSprite					m_itemSprite;			//アイテムのスプライト
	const wchar_t*			m_itemName;				//アイテムの名前
	const wchar_t*			m_textureFilePath;		//テクスチャのファイルパス
	SWeaponStatus			m_equipStatus;			//装備のステータス
};