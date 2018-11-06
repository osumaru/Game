#include "stdafx.h"
#include "ShopNPC.h"
#include "../Camera/GameCamera.h"
#include "../Player/Player.h"
#include "../Item/RecoveryItem.h"
#include "../GameSound/GameSound.h"
#include "../Scene/SceneManager.h"
#include "../Item/RecoveryItem.h"


CShopNPC::CShopNPC()
{
}


CShopNPC::~CShopNPC()
{
}

void CShopNPC::Init(const CVector3 position, const CQuaternion rotation)
{
	m_position = position;
	m_rotation = rotation;
	std::ifstream file;
	
	file.open("NPC/LineupData.txt");
	if (file.fail())
	{
		exit(1);
	}
	for (int num = 0; num < enPotionNum;num++)
	{
		file >> m_lineupPrice[num];
		
	}
	file.close();

	m_skinModel.Load(L"Assets/modelData/U2.cmo",NULL);
	m_backTexture.Load(L"Assets/sprite/MenuUI/Back_Menu.png");
	for (int num = 0;num < BACK_TEXTURE_NUM;num++)
	{
		m_backSprite[num].Init(&m_backTexture);
		m_backSprite[num].SetPosition(m_backPosition);
		m_backSprite[num].SetSize(m_backSize);
		m_backSprite[num].SetAlpha(0.8f);
		m_backPosition.x += BACKTEX_OFFSET_XY.x;
	}

	m_selectTexture.Load(L"Assets/sprite/MenuUI/Select.png");
	m_selectSprite.Init(&m_selectTexture);
	m_selectSprite.SetPosition(m_selectTexPosition);
	m_selectSprite.SetSize({ 50.0f,50.0f });

	m_lineupTexture[0].Load(L"Assets/sprite/ShopUI/BluePotion.png");
	m_lineupTexture[1].Load(L"Assets/sprite/ShopUI/ReadPotion.png");
	m_lineupTexture[2].Load(L"Assets/sprite/ShopUI/GreenPotion.png");
	m_lineupTexture[3].Load(L"Assets/sprite/ShopUI/YellowPotion.png");
	for (int num = 0;num < enPotionNum;num++)
	{
		m_lineupSprite[num].Init(&m_lineupTexture[num]);
		m_lineupSprite[num].SetPosition(m_lineupTexPosition);
		m_lineupSprite[num].SetSize(m_lineupTexSize);
		m_lineupSprite[num].SetAlpha(1.0f);
		m_lineupTexPosition.y  -= 50.0f;
	}
	

	m_shopTexture[0].Load(L"Assets/sprite/ShopUI/Buy.png");
	m_shopTexture[1].Load(L"Assets/sprite/ShopUI/Execute.png");
	CVector2 offsetpos = { -500.0f,200.0f };
	for (int num = 0;num < TEXTURE_NUM;num++)
	{
		m_shopSprite[num].Init(&m_shopTexture[num]);
		m_shopSprite[num].SetSize(m_textureSize);
		m_shopSprite[num].SetPosition(offsetpos);
		offsetpos.y -= 100;

	}
	m_seSound.Init("Assets/sound/Shop/BuySe.wav");
	m_seSound.SetVolume(1.0f);
	

}

void CShopNPC::Update()
{
	CVector3 playervec = GetPlayer().GetPosition() - m_position;
	float len = playervec.Length();
	switch (m_shopState)
	{
	case enShopBuy:
		if (Pad().IsTriggerButton(enButtonDown))
		{
			m_shopState = enShopExecute;
			m_selectTexPosition.y -= 100.0f;
			m_selectSprite.SetPosition(m_selectTexPosition);
		}
		else if (Pad().IsTriggerButton(enButtonX))
		{
			m_drawLineup = true;
			m_shopState = enShopLineup;
			m_selectSprite.SetPosition(LINEUP_SELECT_POSITION);
		}
		break;
	case enShopLineup:
		if (Pad().IsTriggerButton(enButtonX))
		{
			m_isBuy = true;
		}
		if (Pad().IsTriggerButton(enButtonA))
		{
			m_shopState = enShopBuy;
			m_drawLineup = false;
			m_selectSprite.SetPosition(m_selectTexPosition);
		}
		if (Pad().IsTriggerButton(enButtonUp) && m_lineupState != 0)
		{
			int num;
			num = m_lineupState;
			num--;
			m_lineupSelectTexPosition.y += 50.0f;
			m_selectSprite.SetPosition(m_lineupSelectTexPosition);
			m_lineupState = (EnShopLineup)num;

		}
		else if (Pad().IsTriggerButton(enButtonDown) && m_lineupState != enYellowPotion)
		{
			int num;
			num = m_lineupState;
			num++;
			m_lineupSelectTexPosition.y -= 50.0f;
			m_selectSprite.SetPosition(m_lineupSelectTexPosition);
			m_lineupState = (EnShopLineup)num;
		}

		if (!m_isBuy) { break; }
		Transaction(m_lineupPrice[m_lineupState]);
		m_isBuy = false;
		break;

	case enShopExecute:
		if (Pad().IsTriggerButton(enButtonUp))
		{
			m_shopState = enShopBuy;
			m_selectTexPosition.y += 100.0f;
			m_selectSprite.SetPosition(m_selectTexPosition);
			
		}
		else if (Pad().IsTriggerButton(enButtonX))
		{
			m_isTextureDraw = false;
			m_shopState = enShopNone;
			m_selectTexPosition = { -350.0f,200.0f };
			m_selectSprite.SetPosition(m_selectTexPosition);
			GetSceneManager().GetGameScene().GetGameSound()->SetIsShop(false);
			GetPlayer().SetIsActive(true);
		}
		break;
	case enShopNone:
		if (len < SHOP_DRAW_LENGTH)
		{
			if(Pad().IsTriggerButton(enButtonX))
			{ 
				m_isTextureDraw = true;
				m_shopState = enShopBuy;
				GetSceneManager().GetGameScene().GetGameSound()->SetIsShop(true);
				GetPlayer().SetIsActive(false);
			}
			
		}
		break;
	}

	if (m_shopState != enShopNone && len >= SHOP_DRAW_LENGTH)
	{
		m_isTextureDraw = false;
		m_shopState = enShopNone;
		m_selectTexPosition = { -350.0f,200.0f };
		m_selectSprite.SetPosition(m_selectTexPosition);
		GetSceneManager().GetGameScene().GetGameSound()->SetIsShop(false);
	}
	m_skinModel.Update(m_position, m_rotation, m_scale,true);
}
void CShopNPC::Transaction(const int Gold)
{
	//‚¨‹à‚ª‘«‚è‚Ä‚¢‚ê‚Îw“ü‚·‚é‚±‚Æ‚ª‚Å‚«‚é
			if (GetPlayer().BuyMoney(Gold))
			{
				CRecoveryItem* item = new CRecoveryItem;
				item->Init();
				GetPlayer().AddItemList(item);
				CSoundSource* se = New<CSoundSource>(0);
				se->Init("Assets/sound/Shop/BuySe.wav");
				se->SetVolume(1.0f);
				se->Play(false);
			}
}

void CShopNPC::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
	
}
void CShopNPC::AfterDraw()
{
	if (!m_isTextureDraw) { return; }
	
	m_backSprite[0].Draw();
	
	for (int num = 0;num < TEXTURE_NUM;num++)
	{
		m_shopSprite[num].Draw();

	}
	if (!m_drawLineup) { m_selectSprite.Draw(); return; }
	m_backSprite[1].Draw();
	for (int num = 0;num < enPotionNum;num++)
	{
		m_lineupSprite[num].Draw();
	}
	m_selectSprite.Draw();
}