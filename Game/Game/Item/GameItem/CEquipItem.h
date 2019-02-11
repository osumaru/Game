#pragma once
#include "ItemStatus.h"
class CEquipItem 
{
public:
	CEquipItem();
	~CEquipItem();
	bool Start();
	void Update();
	SItemStatus& GetItemStatus(const int num)
	{
		return ItemStatus[num];
	}
	//アイテムのIDが一致するものを取り出す
	//引数	アイテムのID　
	//0を入れたら何も帰ってきません
	SItemStatus& GetItemStatus_ItemId(const int ItemID)
	{
		//if (ItemID == 0 || MAX_ITEM_NUMBER < ItemID){MessageBox(NULL, TEXT("存在しないIDが入力されました。"),TEXT("メッセージボックス"), MB_OK);}
		return ItemStatus[ItemID - 1];
	}
	//ノーマルアイテムのIDの入ったリスト
	//引数　要素数
	const int GetNormalEquipItemList(const int num)
	{
		if (num >= m_normalEquipItemList.size()) { return 0; }
		return m_normalEquipItemList.at(num);
	}
	//ノーマルアイテムのIDの入ったリストの大きさ
	const int GetNormalEquipItemListSize()
	{
		return m_normalEquipItemList.size();
	}
	//レアアイテムのIDの入ったリスト
	//引数　要素数
	const int GetRareItemList(const int num)
	{
		if (num >= m_rareEquipItemList.size()) { return 0; }
		return m_rareEquipItemList.at(num);
	}
	//レアアイテムのIDの入ったリストの大きさ
	const int GetRareEquipItemListSize()
	{
		return m_rareEquipItemList.size();
	}

	//レア3アイテムのIDの入ったリスト
	//引数　要素数
	const int GetLegendEquipItemList(const int num)
	{
		if (num >= m_legendEquipItemList.size()) { return 0; }
		return m_legendEquipItemList.at(num);
	}
	//レア3アイテムのIDの入ったリストの大きさ
	const int GetLegendEquipItemListSize()
	{
		return m_legendEquipItemList.size();
	}
	//レア4アイテムのIDの入ったリスト
	//引数　要素数
	const int GetspecialEquipItemList(const int num)
	{
		if (num >= m_specialEquipItemList.size()) { return 0; }
		return m_specialEquipItemList.at(num);
	}
	//レア4アイテムのIDの入ったリストの大きさ
	const int GetspecialEquipItemListSize()
	{
		return m_specialEquipItemList.size();
	}

private:
	static const int			MAX_ITEM_NUMBER = 40;
	std::list<SItemStatus>		m_equipItemStatusList;
	SItemStatus					ItemStatus[MAX_ITEM_NUMBER];
	SItemStatus					ItemStatus2[MAX_ITEM_NUMBER];
	std::vector<int>			m_normalEquipItemList;			//レア度1のリスト
	std::vector<int>			m_rareEquipItemList;			//レア度3のリスト
	std::vector<int>			m_legendEquipItemList;			//レア度3のリスト
	std::vector<int>			m_specialEquipItemList;			//レア度4のリスト

};

