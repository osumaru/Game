/*
*	インベントリに入れるアイテムのインターフェースクラス
*/
#include "../GameItem/ItemStatus.h"
#pragma once

class IInventoryItem
{
public:
	//コンストラクタ
	IInventoryItem() {};

	//デストラクタ
	virtual ~IInventoryItem() {};

	//初期化
	virtual void Init() {};

	//描画
	virtual void Draw() {};

	//アイテムを使う
	virtual bool Use() { return false; }

	virtual void TexUpdate() {};

	//アイテムのスプライトを取得
	CSprite* GetSprite()
	{
		return &m_itemSprite;
	}

	//アイテムの名前を取得
	wchar_t* GetItemName()
	{
		return m_itemName;
	}

	//ステータスを設定
	void SetStatus(const SItemStatus& status)
	{
		m_status = status;
	}

	//ステータスを取得
	const SItemStatus& GetStatus() const
	{
		return m_status;
	}

protected:
	SItemStatus				m_status;				//アイテムのステータス
	CSprite					m_itemSprite;			//アイテムのスプライト
	wchar_t*				m_itemName;				//アイテムの名前
};