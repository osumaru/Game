#include "stdafx.h"
#include "EquipShopSale.h"
#include "../../Player/Player.h"
#include "../../Item/IItem.h"
#include "../../Player/Weapon/WeaponManager.h"
#include "../../Item/InventoryItem/IInventoryEquip.h"

CEquipShopSale::CEquipShopSale()
{
}

CEquipShopSale::~CEquipShopSale()
{
}

void CEquipShopSale::Init()
{
	m_money.Init(L"0G");
	m_money.SetPosition({ 300.0f, 200.0f });
	//インベントリの幅と高さを初期化
	m_width = 5;
	m_height = CEquipList::m_equipLimit / m_width;
	//座標とサイズを初期化
	m_basePos = { -550.0f, 200.0f };
	m_baseSize = { 100.0f, 100.0f };
	//項目を初期化
	CTexture* texture = TextureResource().LoadTexture(L"Assets/sprite/Weapon.png");
	m_headline.Init(texture);
	m_headline.SetPosition({ -450.0f, 310.0f });
	m_headline.SetSize({ 300.0f, 75.0f });
	//インベントリの背景を初期化
	texture = TextureResource().LoadTexture(L"Assets/sprite/BackGround.png");
	m_background.Init(texture);
	m_background.SetPosition({ 0.0f, 30.0f });
	m_background.SetSize({ 1250.0f, 650.0f });
	//インベントリウィンドウを初期化
	texture = TextureResource().LoadTexture(L"Assets/sprite/InventoryWindow.png");
	m_inventoryWindow.Init(texture);
	m_inventoryWindow.SetPosition({ -350.0f, -10.0f });
	m_inventoryWindow.SetSize({ 530.0f, 560.0f });
	//インベントリの枠を初期化
	texture = TextureResource().LoadTexture(L"Assets/sprite/Frame.png");
	for (int i = 0; i < CEquipList::m_equipLimit; i++)
	{
		m_frame[i].Init(texture);
		m_frame[i].SetSize(m_baseSize);
		CVector2 position = m_basePos;
		position.x += m_baseSize.x * (i % m_width);
		position.y -= m_baseSize.y * (i / m_width);
		m_frame[i].SetPosition(position);
	}

	//ステータスウィンドウの背景を初期化
	texture = TextureResource().LoadTexture(L"Assets/sprite/statusWindow.png");

	m_statusWindow.Init(texture);
	m_statusWindow.SetSize({ 340.0f, 450.0f });
	m_statusWindow.SetPosition({ 100.0f, 30.0f });
	//カーソルを初期化
	texture = TextureResource().LoadTexture(L"Assets/sprite/Pointer.png");
	m_pointer.Init(texture);
	m_pointer.SetPosition(m_basePos);
	m_pointer.SetSize(m_baseSize);


	//装備リストを整理する
	EquipListReset();
	//ステータス表示を初期化
	SplayerStatus playerStatus = GetPlayer().GetStatus();
	CVector2 fontPos = { m_basePos.x + m_baseSize.x * m_width, m_basePos.y - 70.0f };
	wchar_t fontMoji[256];
	wchar_t fontNum[256];
	for (int i = 0; i < CEquipInventory::enStatus_Num; i++)
	{
		switch (i)
		{
		case CEquipInventory::enStatus_Hp:
			swprintf(fontMoji, L"最大HP : ");
			swprintf(fontNum, L"%d", playerStatus.MaxHealth);
			break;
		case CEquipInventory::enStatus_Attack:
			swprintf(fontMoji, L"攻撃力 : ");
			swprintf(fontNum, L"%d", playerStatus.Strength);
			break;
		case CEquipInventory::enStatus_Defense:
			swprintf(fontMoji, L"防御力 : ");
			swprintf(fontNum, L"%d", playerStatus.Defense);
			break;
		}
		m_statusFont[i].Init(fontMoji);
		m_statusFont[i].SetPosition({
			fontPos.x + 30.0f,
			fontPos.y - m_baseSize.y * i
			});
		CVector2 fontSize = { 0.7f, 0.7f };
		m_statusFont[i].SetSize(fontSize);

		m_statusFontNum[i].Init(fontNum);
		m_statusFontNum[i].SetPosition({
			fontPos.x + 160.0f,
			fontPos.y - m_baseSize.y * i
			});
		m_statusFontNum[i].SetSize(fontSize);
	}
	//装備の名前を初期化
	m_equipName.Init(L"");
	m_equipName.SetSize({ 0.7f,0.7f });
	m_equipName.SetPosition({
		m_statusWindow.GetPosition().x - 100.0f,
		fontPos.y + m_baseSize.y - 30.0f
		});


	m_equipSound[0].Init("Assets/sound/SystemSound/EquipOn.wav");
	m_equipSound[1].Init("Assets/sound/SystemSound/EquipOff.wav");
}
void CEquipShopSale::Update()
{
	//カーソル移動
	PointerMove();

	if (Pad().IsTriggerButton(enButtonA))
	{
		
		//アイテムを捨てる
		Sale();
	}

	if (Pad().IsTriggerButton(enButtonB))
	{
		Delete(this);
	}

	wchar_t str[64];
	swprintf(str, L"%dG", GetPlayer().GetStatus().Gold);
	m_money.SetString(str);
	IInventoryEquip* equip = GetEquipList().GetEquip(m_pointerNum);
	if(equip != nullptr)
	{
		m_equipName.SetString(equip->GetItemStatus().ItemName);
		wchar_t attackStr[16];
		swprintf(attackStr, L"%d", equip->GetEquipStatus().attack);
		m_statusFontNum[CEquipInventory::enStatus_Attack].SetString(attackStr);
	}
	else
	{
		m_equipName.SetString(L"");
	}
}

void CEquipShopSale::PostAfterDraw()
{
	m_background.Draw();
	m_headline.Draw();
	m_inventoryWindow.Draw();
	for (int i = 0; i < CEquipList::m_equipLimit; i++)
	{
		m_frame[i].Draw();
	}
	std::list<std::unique_ptr<IInventoryEquip>>& equipList = GetEquipList().GetBody();
	for (auto& equip : equipList)
	{
		equip->Draw();
	}

	m_pointer.Draw();

	m_statusWindow.Draw();

	for (int i = 0; i < CEquipInventory::enStatus_Num; i++)
	{
		m_statusFont[i].Draw();
		m_statusFontNum[i].Draw();
	}
	m_equipName.Draw();
	m_money.Draw();
}

void CEquipShopSale::EquipListReset()
{
	std::list<std::unique_ptr<IInventoryEquip>>& equipList = GetEquipList().GetBody();
	if (equipList.empty())
	{
		//装備が何もない
		return;
	}
	int idx = 0;
	for (auto& equip : equipList)
	{
		//座標を決める
		CVector2 position = m_basePos;
		position.x += m_baseSize.x * (idx % m_width);
		position.y -= m_baseSize.y * (idx / m_width);
		equip->GetSprite()->SetPosition(position);
		equip->GetSprite()->SetSize(m_baseSize);
		idx++;
	}
}

void CEquipShopSale::PointerMove()
{
	CVector2 position = m_pointer.GetPosition();
	int number = m_pointerNum;
	if (Pad().IsTriggerButton(enButtonRight))
	{
		//右にカーソルを動かす
		position.x += m_baseSize.x;
		number++;
		if (position.x >= m_basePos.x + m_baseSize.x * m_width)
		{
			//右端だった場合はそのまま
			position.x = m_basePos.x + m_baseSize.x * (m_width - 1);
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
		position.x -= m_baseSize.x;
		number--;
		if (position.x <= m_basePos.x - m_baseSize.x)
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
		position.y += m_baseSize.y;
		number -= m_width;
		if (position.y >= m_basePos.y + m_baseSize.y)
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
		position.y -= m_baseSize.y;
		number += m_width;
		if (position.y <= m_basePos.y - m_baseSize.y * m_height)
		{
			//下端だった場合はそのまま
			position.y = m_basePos.y - m_baseSize.y * (m_height - 1);
		}
		else
		{
			//動いたらカーソルで選んでいる番号を更新
			m_pointerNum = number;
		}
	}
	//座標を更新
	m_pointer.SetPosition(position);
}


void CEquipShopSale::Sale()
{
	std::list<std::unique_ptr<IInventoryEquip>>& equipList = GetEquipList().GetBody();

	IInventoryEquip* equip = GetEquipList().GetEquip(m_pointerNum);
	if (equip != nullptr)
	{
		const int PRICE_RATE = 5;
		int gold = equip->GetItemStatus().Itemprice / PRICE_RATE;
		GetPlayer().GainGold(gold);
		GetEquipList().Erase(m_pointerNum);
		//装備リストを整理する
		EquipListReset();
		//装備を捨てるときの音を鳴らす処理
		if (m_equipSound[1].IsPlay())
		{
			m_equipSound[1].Stop();
		}
		m_equipSound[1].Play(false, true);
	}
	
}
