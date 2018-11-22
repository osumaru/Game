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
	//�A�C�e����ID����v������̂����o��
	//����	�A�C�e����ID
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
	static const int			MAX_ITEM_NUMBER = 70;
	std::list<SItemStatus>		m_equipItemStatusList;
	SItemStatus					ItemStatus[MAX_ITEM_NUMBER];
};

