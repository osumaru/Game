#pragma once
#include "InventoryItem/IInventoryEquip.h"

class CEquipList
{
public:
	//アイテムを捨てる
//pointerNum	消すアイテムの位置
	void Erase(int pointerNum);

	//所持アイテムリストに追加
	//item		アイテムリストに追加するアイテム
	void AddEquipList(std::unique_ptr<IInventoryEquip> item);

	//アイテムリストを取得
	std::list<std::unique_ptr<IInventoryEquip>>& GetBody()
	{
		return m_equipList;
	}

	//スプライトの座標を設定
	void SetSpritePos(int idx, const CVector2& pos);

	//スプライトのサイズを取得
	void SetSpriteSize(int idx, const CVector2& size);

	//描画
	void Draw();

	//アイテムリストにスペースが空いてるかのフラグを取得
	bool IsSpaceEquipList();

	//アイテムを取得
	//pointerNum 
	IInventoryEquip* GetEquip(int pointerNum);

	static const int m_equipLimit = 15;								//装備所持上限
private:
	std::list<std::unique_ptr<IInventoryEquip>>	m_equipList;//装備リスト
};