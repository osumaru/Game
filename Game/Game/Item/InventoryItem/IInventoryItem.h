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

	void SetStatus(const SItemStatus& status)
	{
		m_status = status;
	}

	const SItemStatus& GetStatus() const
	{
		return m_status;
	}

protected:
	SItemStatus				m_status;
	CSprite					m_itemSprite;			//アイテムのスプライト
	wchar_t*				m_itemName;				//アイテムの名前
};