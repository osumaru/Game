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
private:
	std::list<SItemStatus>		m_equipItemStatusList;
	SItemStatus					ItemStatus[5];
};

