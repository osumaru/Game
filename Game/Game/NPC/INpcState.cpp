#include "stdafx.h"
#include "INpcState.h"
#include "../Player/Player.h"
#include "../Item/RecoveryItem.h"


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
			Transaction(m_items[m_lineupSelectPos.Y][m_lineupSelectPos.X].Itemprice);
		}

		else if (Pad().IsTriggerButton(enButtonUp) && m_lineupSelectPos.Y != 0)
		{
			m_lineupSelectPos.Y--;
			m_slectItemTexPos.y += SHOPLINEUP_POSITION_OFFSET.y;
		}
		else if (Pad().IsTriggerButton(enButtonDown) && m_lineupSelectPos.Y != Y_ELEMENT - 1)
		{
			m_lineupSelectPos.Y++;
			m_slectItemTexPos.y -= SHOPLINEUP_POSITION_OFFSET.y;
		}
		else if (Pad().IsTriggerButton(enButtonLeft) && m_lineupSelectPos.X != 0)
		{
			m_lineupSelectPos.X--;
			m_slectItemTexPos.x -= SHOPLINEUP_POSITION_OFFSET.x;
		}
		else if (Pad().IsTriggerButton(enButtonRight) && m_lineupSelectPos.X != X_ELEMENT - 1)
		{
			m_lineupSelectPos.X++;
			m_slectItemTexPos.x += SHOPLINEUP_POSITION_OFFSET.x;
		}
		m_selectItemSprite.SetPosition(m_slectItemTexPos);
		m_Itemfont.SetString(m_items[m_lineupSelectPos.Y][m_lineupSelectPos.X].ItemName);
		break;
	}

	m_skinModel.Update(m_position, m_rotation, m_scale, true);
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
