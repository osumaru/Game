#pragma once
#include "../Item/InventoryItem/IInventoryItem.h"
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

	void SetSpritePos(int idx, const CVector2& pos);

	void SetSpriteSize(int idx, const CVector2& size);

	void Draw();

	bool IsSpaceItemList();

	static const int	m_itemLimit = 25;			//アイテム所持上限
private:
	std::list<std::unique_ptr<IInventoryItem>>	m_itemList;	//アイテムリスト
};
