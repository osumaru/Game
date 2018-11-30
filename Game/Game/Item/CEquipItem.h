#pragma once
#include "IItem.h"
class CEquipItem:public IItem
{
public:
	CEquipItem();
	~CEquipItem();
	bool Start();
	void Update();
	SItemStatus GetItemStatus(const int num)
	{
		return ItemStatus[num];
	}
	//アイテムのIDが一致するものを取り出す
	//引数	アイテムのID　
	//0を入れたら何も帰ってきません
	SItemStatus GetItemStatus_ItemId(const int ItemID)
	{
		for (auto equiplist : m_equipItemStatusList)
		{
			if (equiplist.ItemID == ItemID)
			{
				return equiplist;
			}
		}
	}
	//ノーマルアイテムのIDの入ったリスト
	const int GetNormalEquipItemList(const int num)
	{
		if (num > m_rareEquipItemList.size()) { return 0; }
		return m_normalEquipItemList.at(num);
	}
	//ノーマルアイテムのIDの入ったリストの大きさ
	const int GetNormalEquipItemListSize()
	{
		return m_normalEquipItemList.size();
	}
	//レアアイテムのIDの入ったリスト
	const int GetRareItemList(const int num)
	{
		if (num > m_rareEquipItemList.size()) { return 0; }
		return m_rareEquipItemList.at(num);
	}
	//レアアイテムのIDの入ったリストの大きさ
	const int GetNormalEquipItemListSize()
	{
		return m_rareEquipItemList.size();
	}

private:
	static const int			MAX_ITEM_NUMBER = 70;
	std::list<SItemStatus>		m_equipItemStatusList;
	SItemStatus					ItemStatus[MAX_ITEM_NUMBER];
	std::vector<int>			m_normalEquipItemList;
	std::vector<int>			m_rareEquipItemList;
};

