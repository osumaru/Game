#include "ItemList.h"

void CItemList::Erase(int pointerNum)
{
	//アイテムの数を取得
	size_t itemNum = m_itemList.size();
	if (pointerNum >= itemNum || m_itemList.empty())
	{
		return;
	}
	std::list<std::unique_ptr<IInventoryItem>>::iterator it;
	it = m_itemList.begin();
	for (int i = 0; i < pointerNum; i++)
	{
		it++;
	}
	//リストから削除する
	m_itemList.erase(it);
	//アイテムを捨てる音を鳴らす
	CSoundSource* eraseItemSound = New<CSoundSource>(0);
	eraseItemSound->Init("Assets/sound/SystemSound/EquipOn.wav");
	eraseItemSound->Play(false);
}

void CItemList::Use(int pointerNum)
{
	size_t itemNum = m_itemList.size();
	if (pointerNum >= itemNum || m_itemList.empty())
	{
		return;
	}
	//選んだアイテムを使う
	std::list<std::unique_ptr<IInventoryItem>>::iterator it;
	it = m_itemList.begin();
	for (int i = 0; i < pointerNum; i++)
	{
		it++;
	}
	bool isUse = (*it)->Use();
	if (isUse)
	{
		//使ったアイテムをリストから削除する
		m_itemList.erase(it);
		//アイテム使用音を鳴らす
		CSoundSource* useItemSound = New<CSoundSource>(0);
		useItemSound->Init("Assets/sound/Battle/heal.wav");
		useItemSound->Play(false);
	}
}

void CItemList::AddItemList(std::unique_ptr<IInventoryItem> item)
{

	if (m_itemList.size() < m_itemLimit)
	{
		//所持上限を超えていなければアイテムリストに追加
		m_itemList.push_back(std::move(item));
	}
}

void CItemList::SetSpritePos(int idx, const CVector2 & pos)
{
	size_t itemNum = m_itemList.size();
	if (idx >= itemNum || m_itemList.empty())
	{
		return;
	}
	std::list<std::unique_ptr<IInventoryItem>>::iterator it;
	it = m_itemList.begin();
	for (int i = 0; i < idx; i++)
	{
		it++;
	}
	//リストから削除する
	(*it)->GetSprite()->SetPosition(pos);
}

void CItemList::SetSpriteSize(int idx, const CVector2 & size)
{
	size_t itemNum = m_itemList.size();
	if (idx >= itemNum || m_itemList.empty())
	{
		return;
	}
	std::list<std::unique_ptr<IInventoryItem>>::iterator it;
	it = m_itemList.begin();
	for (int i = 0; i < idx; i++)
	{
		it++;
	}
	//リストから削除する
	(*it)->GetSprite()->SetSize(size);
}

void CItemList::Draw()
{
	for (auto& item : m_itemList)
	{
		item->Draw();
	}
}

bool CItemList::IsSpaceItemList()
{
	if (m_itemList.size() < m_itemLimit)
	{
		//リストに空きがある
		return true;
	}
	return false;
}

IInventoryItem * CItemList::GetItem(int pointerNum)
{
	size_t itemNum = m_itemList.size();
	if (pointerNum >= itemNum || m_itemList.empty())
	{
		return nullptr;
	}
	std::list<std::unique_ptr<IInventoryItem>>::iterator it;
	it = m_itemList.begin();
	for (int i = 0; i < pointerNum; i++)
	{
		it++;
	}
	return (*it).get();
}
