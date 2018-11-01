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

	CVector2			m_basePos = CVector2::Zero;
	CVector2			m_size = CVector2::Zero;

	int					m_inventoryWidth = 0;
	int					m_inventoryHeight = 0;

	int					m_pointerNum = 0;
};