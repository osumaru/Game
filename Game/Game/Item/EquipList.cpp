#include "EquipList.h"

void CEquipList::Erase(int pointerNum)
{
	//�A�C�e���̐����擾
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
	//���X�g����폜����
	m_equipList.erase(it);
}

void CEquipList::AddEquipList(std::unique_ptr<IInventoryEquip> item)
{
	if (m_equipList.size() < m_equipLimit)
	{
		//��������𒴂��Ă��Ȃ���΃A�C�e�����X�g�ɒǉ�
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
	//���X�g����폜����
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
	//���X�g����폜����
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
		//���X�g�ɋ󂫂�����
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
