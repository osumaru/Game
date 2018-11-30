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
	//����	�A�C�e����ID�@
	//0����ꂽ�牽���A���Ă��܂���
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
	//�m�[�}���A�C�e����ID�̓��������X�g
	const int GetNormalEquipItemList(const int num)
	{
		if (num > m_rareEquipItemList.size()) { return 0; }
		return m_normalEquipItemList.at(num);
	}
	//�m�[�}���A�C�e����ID�̓��������X�g�̑傫��
	const int GetNormalEquipItemListSize()
	{
		return m_normalEquipItemList.size();
	}
	//���A�A�C�e����ID�̓��������X�g
	const int GetRareItemList(const int num)
	{
		if (num > m_rareEquipItemList.size()) { return 0; }
		return m_rareEquipItemList.at(num);
	}
	//���A�A�C�e����ID�̓��������X�g�̑傫��
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

