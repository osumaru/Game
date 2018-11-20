#include "stdafx.h"
#include "IShop.h"
#include "../Player/Player.h"
#include "../GameSound/GameSound.h"
#include "../Scene/SceneManager.h"
#include "../Item/RecoveryItem.h"



IShop::IShop()
{
}


IShop::~IShop()
{
}

void IShop::ShopUpdate()
{
	CVector3 playervec = GetPlayer().GetPosition() - m_position;
	float len = playervec.Length();

	switch (m_shopState)
	{
	case enShopNone:
		//�v���C���[�ƃV���b�v�Ƃ̋��������ȓ���A�{�^���������ꂽ��X���J��
		if (len < SHOP_DRAW_LENGTH)
		{
			if (Pad().IsTriggerButton(enButtonA))
			{

				m_shopState = enShopOpen;
				m_selectShop = enShopBuy;
				m_isSelectDraw = true;
				GetPlayer().SetIsActiveUpdate(false);
				//�X�p�̉��y��������
				GetSceneGame().GetGameSound()->SetIsShop(true);
				
				
			}
		}
		break;
	case enShopOpen:
		if (Pad().IsTriggerButton(enButtonA))
		{
			m_shopState = m_selectShop;
			if (m_shopState == enShopBuy) { m_isShoplineupDraw = true; }
			else 
			{ 
				GetPlayer().SetIsActiveUpdate(true); 
				GetSceneGame().GetGameSound()->SetIsShop(false);
			}
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
		if (Pad().IsTriggerButton(enButtonB))
		{
			m_shopState = enShopNone;
			m_isShoplineupDraw = false;
			GetPlayer().SetIsActiveUpdate(true);
			GetSceneGame().GetGameSound()->SetIsShop(false);
		}
		else if (Pad().IsTriggerButton(enButtonA))
		{
			//������s��
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

	m_skinModel.Update(m_position, m_rotation, m_scale, false);
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
	//����������Ă���΍w�����邱�Ƃ��ł���
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