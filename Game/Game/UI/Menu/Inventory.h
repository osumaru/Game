#pragma once

class CMenu;
class IItem;

class CInventory : public IGameObject
{
public:
	CInventory();
	~CInventory();

	void Init(CMenu* menu);

	bool Start() override;

	void Update() override;

	void AfterDraw() override;

private:
	static const int	m_itemLimit = 15;
	CSprite				m_inventory;
	CTexture			m_inventoryTexture;
	CSprite				m_pointer;
	CTexture			m_pointerTexture;

	CSprite				m_recoveryItem[m_itemLimit];
	std::list<IItem*>	m_itemList;

	CMenu*				m_menu = nullptr;
};