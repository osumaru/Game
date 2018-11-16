#include "stdafx.h"
#include "INpcState.h"
#include "../Player/Player.h"
#include "../Item/RecoveryItem.h"
#include "../Player/Weapon.h"



INpcState::INpcState()
{
}


INpcState::~INpcState()
{
}

void INpcState::ShopUpdate()
{
	CVector3 playervec = GetPlayer().GetPosition() - m_position;
	float len = playervec.Length();

	switch (m_shopState)
	{
	case enShopNone:
		if (len < SHOP_DRAW_LENGTH)
		{
			if (Pad().IsTriggerButton(enButtonX))
			{

				m_shopState = enShopOpen;
				m_selectShop = enShopBuy;
				m_isSelectDraw = true;
			}
		}
		break;
	case enShopOpen:
		if (Pad().IsTriggerButton(enButtonX))
		{
			m_shopState = m_selectShop;
			if (m_shopState == enShopBuy) { m_isShoplineupDraw = true; }
			m_isSelectDraw = false;
			m_shopSelectPenPosition = SELECT_POSITON_START;
			m_shopSelectPen.SetPosition(m_shopSelectPenPosition);
		}

		else if (Pad().IsTriggerButton(enButtonDown) && m_selectShop != enShopNone)
		{
			m_selectShop = enShopNone;
			m_shopSelectPenPosition.y -= 100.0f;
			m_shopSelectPen.SetPosition(m_shopSelectPenPosition);
		}
		else if (Pad().IsTriggerButton(enButtonUp) && m_selectShop != enShopBuy)
		{
			m_selectShop = enShopBuy;
			m_shopSelectPenPosition.y += 100.0f;
			m_shopSelectPen.SetPosition(m_shopSelectPenPosition);
		}

		break;
	case enShopBuy:
		if (Pad().IsTriggerButton(enButtonA))
		{
			m_shopState = enShopNone;
			m_isShoplineupDraw = false;
		}
		else if (Pad().IsTriggerButton(enButtonX))
		{
			//Žæˆø‚ðs‚¤
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
	}
	
	if (len >= SHOP_DRAW_LENGTH)
	{
		m_shopState = enShopNone;
		m_selectShop = enShopBuy;
		m_isSelectDraw = false;
		m_isShoplineupDraw = false;
	}

	m_skinModel.Update(m_position, m_rotation, m_scale, true);
}
void INpcState::LoadFile(const wchar_t* filePath)
{
	std::fstream	file;
	file.open(filePath, std::ios::binary | std::ios::in);
	file.read((char*)&m_itemState, sizeof(ItemState));
	int num = file.tellg();
	file.close();
}
void INpcState::AddFile(const wchar_t* filePath)
{
	std::fstream	file;
	swprintf(m_itemState.ItemName, L"osakanasan");
	m_itemState.ItemID = 1;
	m_itemState.Itemprice = 100;
	file.open(filePath, std::ios::binary | std::ios::out );
	file.write((char*)&m_itemState, sizeof(m_itemState));
	file.close();
}

bool INpcState::Transaction(const int gold)
{
	//‚¨‹à‚ª‘«‚è‚Ä‚¢‚ê‚Îw“ü‚·‚é‚±‚Æ‚ª‚Å‚«‚é
	if (GetPlayer().BuyMoney(gold))
	{
		CRecoveryItem* item = new CRecoveryItem;
		item->Init();
		GetPlayer().AddItemList(item);
		CSoundSource* se = New<CSoundSource>(0);
		se->Init("Assets/sound/Shop/BuySe.wav");
		se->SetVolume(1.0f);
		se->Play(false);
		return true;
	}
	else 
	{
		return false;
	}
}
