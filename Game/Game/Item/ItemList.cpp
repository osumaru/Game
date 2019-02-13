#include "ItemList.h"

void CItemList::Erase(int pointerNum)
{
	//�A�C�e���̐����擾
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
	//���X�g����폜����
	m_itemList.erase(it);
	//�A�C�e�����̂Ă鉹��炷
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
	//�I�񂾃A�C�e�����g��
	std::list<std::unique_ptr<IInventoryItem>>::iterator it;
	it = m_itemList.begin();
	for (int i = 0; i < pointerNum; i++)
	{
		it++;
	}
	bool isUse = (*it)->Use();
	if (isUse)
	{
		//�g�����A�C�e�������X�g����폜����
		m_itemList.erase(it);
		//�A�C�e���g�p����炷
		CSoundSource* useItemSound = New<CSoundSource>(0);
		useItemSound->Init("Assets/sound/Battle/heal.wav");
		useItemSound->Play(false);
	}
}

void CItemList::AddItemList(std::unique_ptr<IInventoryItem> item)
{

	if (m_itemList.size() < m_itemLimit)
	{
		//��������𒴂��Ă��Ȃ���΃A�C�e�����X�g�ɒǉ�
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
	//���X�g����폜����
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
	//���X�g����폜����
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
		//���X�g�ɋ󂫂�����
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
