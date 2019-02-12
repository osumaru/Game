#include "stdafx.h"
#include "IShop.h"
#include "../Player/Player.h"
#include "../GameSound/GameSound.h"
#include "../Scene/SceneManager.h"
#include "../Item/InventoryItem/IInventoryItem.h"
#include "../Item/InventoryItem/InventoryRecoveryItem.h"
#include "../UI/Menu/ItemInventory.h"
#include "../UI/ShopSale/ItemShopSale.h"
#include "../UI/ShopSale/EquipShopSale.h"

IShop::IShop()
{
	m_money.Init(L"0");
	m_money.SetPosition({400.0f, 300.0f});
	m_moneyBack.Init(TextureResource().LoadTexture(L"Assets/sprite/ShopUI/Back_Menu.png"));
	m_moneyBack.SetSize({150.0f, 50.0f});
	m_moneyBack.SetCenterPosition({ 0.0f, 0.0f });
	m_moneyBack.SetPosition({ 400.0f, 300.0f });
}


IShop::~IShop()
{
}

void IShop::ShopUpdate()
{
	if (&GetPlayer() == nullptr) { return; }
	CVector3 playervec = GetPlayer().GetPosition() - m_position;
	float len = playervec.Length();
	switch (m_shopState)
	{
	case enShopNone:
		//プレイヤーとショップとの距離が一定以内でAボタンが押されたら店を開く
		if (len < SHOP_DRAW_LENGTH)
		{
			//店員の前方向取得
			CVector3 flont = { m_skinmodelNpc.GetWorldMatrix().m[2][0],
								m_skinmodelNpc.GetWorldMatrix().m[2][1],
								m_skinmodelNpc.GetWorldMatrix().m[2][2] };
			flont.Normalize();
			playervec.Normalize();
			float angle = flont.Dot(playervec);
			angle = acos(angle);
			if (Pad().IsTriggerButton(enButtonA) && fabsf(angle) < CMath::DegToRad(40.0f))
			{
				m_shopState = enShopOpen;
				m_selectShop = enShopBuy;
				m_isSelectDraw = true;
				GetPlayer().SetIsActiveUpdate(false);
				//店用の音楽をかける
				GetSceneManager().GetGameSound()->SetGameSound(CGameSound::enShopBgm);
			}
		}
		break;
	case enShopOpen:
		if (Pad().IsTriggerButton(enButtonA))
		{
			m_shopState = m_selectShop;
			if (m_shopState == enShopBuy) { m_isShoplineupDraw = true; }
			else if (m_shopState == enShopSale)
			{
				//店の種類によって出す売却用のUIを変える
				switch (m_shopType)
				{
				case enItemShop:
					New<CItemShopSale>(PRIORITY_UI)->Init();
					break;
				case enWeaponShop:
					New<CEquipShopSale>(PRIORITY_UI)->Init();
					break;
				case enNormalNpc:
					break;
				}
				m_shopState = enShopSale;
			}
			else 
			{ 
				GetPlayer().SetIsActiveUpdate(true); 
				//GetSceneGame().GetGameSound()->SetIsShop(false);
				GetSceneManager().GetGameSound()->SetGameSound(CGameSound::enWorldBgm);
			}
			m_isSelectDraw = false;
			m_shopSelectPenPosition = SELECT_POSITON_START;
			m_shopSelectPen.SetPosition(m_shopSelectPenPosition);

		}
		else if (Pad().IsTriggerButton(enButtonDown))
		{
			switch (m_selectShop)
			{
			case enShopBuy:
				m_selectShop = enShopSale;
				break;
			case enShopSale:
				m_selectShop = enShopNone;
				break;
			case enShopNone:
				m_shopSelectPenPosition.y += 70.0f;
				break;
			}
			m_shopSelectPenPosition.y -= 70.0f;
			m_shopSelectPen.SetPosition(m_shopSelectPenPosition);
			GetPlayer().SetIsAction(false);
		}
		else if (Pad().IsTriggerButton(enButtonUp))
		{
			switch (m_selectShop)
			{
			case enShopBuy:
				m_shopSelectPenPosition.y -= 70.0f;
				break;
			case enShopSale:
				m_selectShop = enShopBuy;
				break;
			case enShopNone:
				m_selectShop = enShopSale;
				break;
			}
			m_shopSelectPenPosition.y += 70.0f;
			m_shopSelectPen.SetPosition(m_shopSelectPenPosition);
		}
		if (Pad().IsTriggerButton(enButtonB))
		{
			m_shopState = enShopNone;
			m_isSelectDraw = false;
			GetPlayer().SetIsActiveUpdate(true);
			GetPlayer().SetIsAction(false);
			m_shopSelectPenPosition = SELECT_POSITON_START;
			m_shopSelectPen.SetPosition(m_shopSelectPenPosition);
			//GetSceneGame().GetGameSound()->SetIsShop(false);
			GetSceneManager().GetGameSound()->SetGameSound(CGameSound::enWorldBgm);

		}

		break;
	case enShopBuy:
		if (Pad().IsTriggerButton(enButtonB))
		{
			m_shopState = enShopOpen;
			m_isShoplineupDraw = false;
			m_isSelectDraw = true;
			//GetSceneGame().GetGameSound()->SetIsShop(false);
			GetSceneManager().GetGameSound()->SetGameSound(CGameSound::enWorldBgm);
		}
		else if (Pad().IsTriggerButton(enButtonA))
		{
			//取引を行う
			m_isTransaction = true;
		}

		else if (Pad().IsTriggerButton(enButtonUp) && m_lineupSelectNumber != 0)
		{
			m_lineupSelectNumber--;
			m_slectItemTexPos.y += SHOPLINEUP_POSITION_OFFSET.y;
		}
		else if (Pad().IsTriggerButton(enButtonDown) && m_lineupSelectNumber != ITEM_ELEMENT - 1)
		{
			m_lineupSelectNumber++;
			m_slectItemTexPos.y -= SHOPLINEUP_POSITION_OFFSET.y;
		}
		m_selectItemSprite.SetPosition(m_slectItemTexPos); 

		break;
	case enShopSale:
		if (Pad().IsTriggerButton(enButtonB))
		{
			m_selectShop = enShopBuy;
			m_shopState = enShopOpen;
			m_shopSelectPenPosition = SELECT_POSITON_START;
			m_shopSelectPen.SetPosition(m_shopSelectPenPosition);
			m_isSelectDraw = true;
		}
		break;
	}
	int gold = GetPlayer().GetStatus().Gold;
	wchar_t str[64];
	swprintf(str, L"%d", gold);
	m_money.SetString(str);
	m_animation.Update(GameTime().GetDeltaFrameTime());
	m_skinModel.Update(m_position, m_rotation, m_scale, false);
	m_skinmodelNpc.Update(m_position, m_rotation, m_scale, true);
}
void IShop::LoadFile(const wchar_t* filePath)
{
	std::fstream	file;
	file.open(filePath, std::ios::binary | std::ios::in);
	int num = file.tellg();
	file.close();
}
void IShop::AddFile(const wchar_t* filePath)
{
	/*std::fstream	file;
	m_itemState.ItemID = 1;
	m_itemState.Itemprice = 100;
	file.open(filePath, std::ios::binary | std::ios::out );
	file.write((char*)&m_itemState, sizeof(m_itemState));
	file.close();*/
}

bool IShop::Transaction(const int gold)
{
	//お金が足りていれば購入することができる
	if (GetPlayer().BuyMoney(gold))
	{
		std::unique_ptr<IInventoryItem> inventoryItem = std::make_unique<CInventoryRecoveryItem>();
		inventoryItem->Init();
		GetItemList().AddItemList(std::move(inventoryItem));
		CSoundSource* se = New<CSoundSource>(0);
		se->Init("Assets/sound/SystemSound/BuySe.wav");
		se->SetVolume(1.0f);
		se->Play(false);
		return true;
	}
	else 
	{
		return false;
	}
}
