#include "stdafx.h"
#include "ShopNPC.h"
#include "../Camera/GameCamera.h"
#include "../Player/Player.h"
#include "../Itam/RecoveryItem.h"


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

	m_skinModel.Load(L"Assets/modelData/U2.cmo",NULL);
	m_backTexture.Load(L"Assets/sprite/MenuUI/Back_Menu.png");
	m_backSprite.Init(&m_backTexture);
	m_backSprite.SetPosition({ -480.0f,0.0f });
	m_backSprite.SetSize({ 320.0f,600.0f });
	m_backSprite.SetAlpha(0.8f);

	m_selectTexture.Load(L"Assets/sprite/MenuUI/Select.png");
	m_selectSprite.Init(&m_selectTexture);
	m_selectSprite.SetPosition(m_selectTexPosition);
	m_selectSprite.SetSize({ 50.0f,50.0f });

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
	m_bgmSound.Init("Assets/sound/Shop/ShopBgm.wav");
	m_seSound.Init("Assets/sound/Shop/BuySe.wav");
	m_bgmSound.SetVolume(1.0f);
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
			//‚¨‹à‚ª‘«‚è‚Ä‚¢‚ê‚Îw“ü‚·‚é‚±‚Æ‚ª‚Å‚«‚é
			if (GetPlayer().BuyMoney(RECOVERY_MONEY))
			{
				CRecoveryItem* item = new CRecoveryItem;
				GetPlayer().AddItemList(item);
				CSoundSource* se = new CSoundSource;
				se->Init("Assets/sound/Shop/BuySe.wav");
				se->SetVolume(1.0f);
				se->Play(true);
			}
		}
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
			m_bgmSound.Stop();
		}
		break;
	case enShopNone:
		if (len < SHOP_DRAW_LENGTH)
		{
			if(Pad().IsTriggerButton(enButtonX))
			{ 
				m_isTextureDraw = true;
				m_shopState = enShopBuy;
				m_bgmSound.Play(true,true);
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
		m_bgmSound.Stop();
	}
	m_skinModel.Update(m_position, m_rotation, m_scale,true);
}

void CShopNPC::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
	
}
void CShopNPC::AfterDraw()
{
	if (!m_isTextureDraw) { return; }
	m_backSprite.Draw();
	m_selectSprite.Draw();
	for (int num = 0;num < TEXTURE_NUM;num++)
	{
		m_shopSprite[num].Draw();

	}
}