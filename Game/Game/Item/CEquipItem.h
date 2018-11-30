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
	const int GetNormalItemList(const int num)
	{
		if (num > NORMAL_ITEM) { return 0; }
		return NORMAL_EQUIP_ITEM[num];
	}
	//���A�A�C�e����ID�̓��������X�g
	const int GetRareItemList(const int num)
	{
		if (num > RARE_ITEM) { return 0; }
		return RARE_EQUIP_ITEM[num];
	}

private:
	static const int			MAX_ITEM_NUMBER = 70;
	std::list<SItemStatus>		m_equipItemStatusList;
	SItemStatus					ItemStatus[MAX_ITEM_NUMBER];
	const int					NORMAL_ITEM = 7;
	const int					RARE_ITEM = 11;
	const int					NORMAL_EQUIP_ITEM[7] = { 1,2,3,11,12,13,14 };
	const int					RARE_EQUIP_ITEM[11] = { 4,5,6,7,8,9,15,16,17,18,19};
};

