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
void CShopNPC::Update()
{
	
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
	
}
