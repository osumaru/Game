#pragma once
#include "ItemStatus.h"
class CEquipItem 
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
		if (ItemID == 0 || MAX_ITEM_NUMBER < ItemID){MessageBox(NULL, TEXT("���݂��Ȃ�ID�����͂���܂����B"),TEXT("���b�Z�[�W�{�b�N�X"), MB_OK);}
		return ItemStatus[ItemID - 1];
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
	const int GetRareEquipItemListSize()
	{
		return m_rareEquipItemList.size();
	}

private:
	static const int			MAX_ITEM_NUMBER = 30;
	std::list<SItemStatus>		m_equipItemStatusList;
	SItemStatus					ItemStatus[MAX_ITEM_NUMBER];
	std::vector<int>			m_normalEquipItemList;
	std::vector<int>			m_rareEquipItemList;
};

