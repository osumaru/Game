#pragma once

class IIventoryEquip 
{
	//コンストラクタ
	IIventoryEquip() {};

	//デストラクタ
	virtual ~IIventoryEquip() {};

	//初期化
	virtual void Init() {};

	//描画
	virtual void Draw() {};

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

protected:
	CSprite					m_itemSprite;			//アイテムのスプライト
	wchar_t*				m_itemName;				//アイテムの名前
};