#pragma once
#include "ItemStatus.h"
class CQuickItem 
{
public:
	CQuickItem();
	~CQuickItem();
	bool Start();
	void Update();
	SItemStatus& GetItemStatus(const int num)
	{
		return ItemStatus[num];
	}
	//�A�C�e����ID����v������̂����o��
	//����	�A�C�e����ID
	SItemStatus& GetItemStatus_ItemId(const int ItemID)
	{
		for (auto quicklist : m_quickItemStatusList)
		{
			if (quicklist.ItemID == ItemID)
			{
				return quicklist;
			}
		}
	}
	//�A�C�e���̎�ނ��擾
	int GetMaxItemNum()
	{
		return MAX_QUICK_ITEM_LIST;
	}
private:
	static const int			MAX_QUICK_ITEM_LIST = 3;
	std::list<SItemStatus>		m_quickItemStatusList;
	SItemStatus					ItemStatus[MAX_QUICK_ITEM_LIST];
};

