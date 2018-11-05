#include "stdafx.h"
#include "EquipInventory.h"
#include "Menu.h"
#include "../../Player/Player.h"
#include "../../Item/IItem.h"

CEquipInventory::CEquipInventory(){}

CEquipInventory::~CEquipInventory(){}

void CEquipInventory::Init(CMenu * menu)
{
	m_menu = menu;
	//座標とサイズを初期化
	m_basePos = { -560.0f, 180.0f };
	m_size = { 150.0f, 150.0f };
	//インベントリの背景を初期化
	m_backGroundTexture.Load(L"Assets/sprite/MenuUI/Back_Menu.png");
	m_backGround.Init(&m_backGroundTexture);
	//カーソルを初期化
	m_pointerTexture.Load(L"Assets/sprite/Pointer.png");
	m_pointer.Init(&m_pointerTexture);
	m_pointer.SetPosition(m_basePos);
	m_pointer.SetSize(m_size);
	//装備リストを取得
	m_equipList = GetPlayer().GetEquipList();
	m_width = 5;
	m_height = 1;
	if (!m_equipList.empty()) {
		//リストにアイテムがある
		int idx = 0;
		for (auto& equip : m_equipList)
		{
			//アイテムの種類を取得
			CWeapon::EnPlayerWeapon weaponNum = equip.weaponNum;
			if (weaponNum == CWeapon::enSword)
			{
				//剣
				CTexture* itemTexure = TextureResource().LoadTexture(L"Assets/sprite/sword.png");
				m_equip[idx].Init(itemTexure);
			}
			else if (weaponNum == CWeapon::enLongSword)
			{
				//大剣
				CTexture* itemTexure = TextureResource().LoadTexture(L"Assets/sprite/largeSword.png");
				m_equip[idx].Init(itemTexure);
			}
			else if (weaponNum == CWeapon::enArrow)
			{
				//弓
				CTexture* itemTexure = TextureResource().LoadTexture(L"Assets/sprite/bow.png");
				m_equip[idx].Init(itemTexure);
			}
			else if (weaponNum == CWeapon::enTwinSword)
			{
				//双剣
				CTexture* itemTexure = TextureResource().LoadTexture(L"Assets/sprite/twinSword.png");
				m_equip[idx].Init(itemTexure);
			}
			//座標とサイズを決める
			CVector2 position = m_basePos;
			position.x += m_size.x * (idx % m_width);
			position.y -= m_size.y * (idx / m_width);
			if (idx != 0 && idx % m_width == 0)
			{
				//インベントリの幅を超えたら行を下げる
				m_height++;
			}
			m_equip[idx].SetPosition(position);
			m_equip[idx].SetSize(m_size);
			idx++;
		}
	}

}

bool CEquipInventory::Start()
{
	m_menu->SetIsActive(false);
	return true;
}

void CEquipInventory::Update()
{
	//装備の数を取得
	size_t equipNum = m_equipList.size();
	int number = m_pointerNum;
	CVector2 position = m_pointer.GetPosition();
	float offset = m_size.x / 2.0f;
	if (Pad().IsTriggerButton(enButtonRight))
	{
		//右にカーソルを動かす
		position.x += m_size.x;
		number++;
		if (position.x > m_basePos.x + m_size.x * (m_width - 1) + offset)
		{
			//右端だった場合はそのまま
			position.x = m_basePos.x + m_size.x * (m_width - 1);
		}
		else
		{
			//動いたらカーソルで選んでいる番号を更新
			m_pointerNum = number;
		}
	}
	else if (Pad().IsTriggerButton(enButtonLeft))
	{
		//左にカーソルを動かす
		position.x -= m_size.x;
		number--;
		if (position.x < m_basePos.x - offset)
		{
			//左端だった場合はそのまま
			position.x = m_basePos.x;
		}
		else
		{
			//動いたらカーソルで選んでいる番号を更新
			m_pointerNum = number;
		}
	}
	else if (Pad().IsTriggerButton(enButtonUp))
	{
		//上にカーソルを動かす
		position.y += m_size.y;
		number -= m_width;
		if (position.y > m_basePos.y + offset)
		{
			//上端だった場合はそのまま
			position.y = m_basePos.y;
		}
		else
		{
			//動いたらカーソルで選んでいる番号を更新
			m_pointerNum = number;
		}
	}
	else if (Pad().IsTriggerButton(enButtonDown))
	{
		//下にカーソルを動かす
		position.y -= m_size.y;
		number += m_width;
		if (position.y < m_basePos.y - m_size.y * (m_height - 1) - offset)
		{
			//下端だった場合はそのまま
			position.y = m_basePos.y - m_size.y * (m_height - 1);
		}
		else
		{
			//動いたらカーソルで選んでいる番号を更新
			m_pointerNum = number;
		}
	}
	//座標を更新
	m_pointer.SetPosition(position);

	if (m_pointerNum < equipNum && Pad().IsTriggerButton(enButtonA))
	{
		//カーソルで選んでいる装備をつける
		GetPlayer().ChangeEquip(m_pointerNum);
		m_equipList = GetPlayer().GetEquipList();
		m_width = 5;
		m_height = 1;
		if (!m_equipList.empty()) {
			//リストにアイテムがある
			int idx = 0;
			for (auto& equip : m_equipList)
			{
				//アイテムの種類を取得
				CWeapon::EnPlayerWeapon weaponNum = equip.weaponNum;
				if (weaponNum == CWeapon::enSword)
				{
					//剣
					CTexture* itemTexure = TextureResource().LoadTexture(L"Assets/sprite/sword.png");
					m_equip[idx].SetTexture(itemTexure);
				}
				else if (weaponNum == CWeapon::enLongSword)
				{
					//大剣
					CTexture* itemTexure = TextureResource().LoadTexture(L"Assets/sprite/largeSword.png");
					m_equip[idx].SetTexture(itemTexure);
				}
				else if (weaponNum == CWeapon::enArrow)
				{
					//弓
					CTexture* itemTexure = TextureResource().LoadTexture(L"Assets/sprite/bow.png");
					m_equip[idx].SetTexture(itemTexure);
				}
				else if (weaponNum == CWeapon::enTwinSword)
				{
					//双剣
					CTexture* itemTexure = TextureResource().LoadTexture(L"Assets/sprite/twinSword.png");
					m_equip[idx].SetTexture(itemTexure);
				}
				//座標とサイズを決める
				CVector2 position = m_basePos;
				position.x += m_size.x * (idx % m_width);
				position.y -= m_size.y * (idx / m_width);
				if (idx != 0 && idx % m_width == 0)
				{
					//インベントリの幅を超えたら行を下げる
					m_height++;
				}
				m_equip[idx].SetPosition(position);
				m_equip[idx].SetSize(m_size);
				idx++;
			}
		}
	}

	if (Pad().IsTriggerButton(enButtonB)) {
		//メニューに戻る
		m_menu->SetIsActive(true);
		Delete(this);
	}
}

void CEquipInventory::AfterDraw()
{
	m_backGround.Draw();
	for (int i = 0; i < m_equipList.size(); i++) {
		m_equip[i].Draw();
	}
	m_pointer.Draw();
}
