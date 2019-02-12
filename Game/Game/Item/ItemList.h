#pragma once
#pragma once
#include "InventoryItem/IInventoryItem.h"
//プレイヤーの所持しているアイテムのリスト

class CItemList
{
public:
	//アイテムを捨てる
	//pointerNum	消すアイテムの位置
	void Erase(int pointerNum);

	void Use(int pointerNum);

	//所持アイテムリストに追加
	//item		アイテムリストに追加するアイテム
	void AddItemList(std::unique_ptr<IInventoryItem> item);

	//アイテムリストを取得
	std::list<std::unique_ptr<IInventoryItem>>& GetBody()
	{
		return m_itemList;
	}

	//スプライトの座標を設定
	void SetSpritePos(int idx, const CVector2& pos);

	//スプライトのサイズを取得
	void SetSpriteSize(int idx, const CVector2& size);

	//描画
	void Draw();

	//アイテムリストにスペースが空いてるかのフラグを取得
	bool IsSpaceItemList();

	//アイテムを取得
	//pointerNum 
	IInventoryItem* GetItem(int pointerNum);

	static const int	m_itemLimit = 25;			//アイテム所持上限
private:
	std::list<std::unique_ptr<IInventoryItem>>	m_itemList;	//アイテムリスト
};
