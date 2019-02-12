#include "EquipList.h"

void CEquipList::Erase(int pointerNum)
{
	//アイテムの数を取得
	size_t itemNum = m_equipList.size();
	if (pointerNum >= itemNum || m_equipList.empty())
	{
		return;
	}
	std::list<std::unique_ptr<IInventoryEquip>>::iterator it;
	it = m_equipList.begin();
	for (int i = 0; i < pointerNum; i++)
	{
		it++;
	}
	//リストから削除する
	m_equipList.erase(it);
}

void CEquipList::AddEquipList(std::unique_ptr<IInventoryEquip> item)
{
	if (m_equipList.size() < m_equipLimit)
	{
		//所持上限を超えていなければアイテムリストに追加
		m_equipList.push_back(std::move(item));
	}
}

void CEquipList::SetSpritePos(int idx, const CVector2 & pos)
{
	size_t itemNum = m_equipList.size();
	if (idx >= itemNum || m_equipList.empty())
	{
		return;
	}
	std::list<std::unique_ptr<IInventoryEquip>>::iterator it;
	it = m_equipList.begin();
	for (int i = 0; i < idx; i++)
	{
		it++;
	}
	//リストから削除する
	(*it)->GetSprite()->SetPosition(pos);
}

void CEquipList::SetSpriteSize(int idx, const CVector2 & size)
{
	size_t itemNum = m_equipList.size();
	if (idx >= itemNum || m_equipList.empty())
	{
		return;
	}
	std::list<std::unique_ptr<IInventoryEquip>>::iterator it;
	it = m_equipList.begin();
	for (int i = 0; i < idx; i++)
	{
		it++;
	}
	//リストから削除する
	(*it)->GetSprite()->SetSize(size);
}

void CEquipList::Draw()
{
	for (auto& item : m_equipList)
	{
		item->Draw();
	}
}

bool CEquipList::IsSpaceEquipList()
{
	if (m_equipList.size() < m_equipLimit)
	{
		//リストに空きがある
		return true;
	}
	return false;
}

IInventoryEquip * CEquipList::GetEquip(int pointerNum)
{
	size_t itemNum = m_equipList.size();
	if (pointerNum >= itemNum || m_equipList.empty())
	{
		return nullptr;
	}
	std::list<std::unique_ptr<IInventoryEquip>>::iterator it;
	it = m_equipList.begin();
	for (int i = 0; i < pointerNum; i++)
	{
		it++;
	}
	return (*it).get();
}
