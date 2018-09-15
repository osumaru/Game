#include "stdafx.h"
#include "PlayerHp.h"
#include "../../Player/Player.h"

void CPlayerHp::Init()
{
	//1 現在のHP量をHPゲージのXのサイズにそのまま入れる

	/*2 最大HPを取得してきて　現在HP%最大HP＝余り(1以下)　<余り*100>これをXのサイズに入れる？
	HPバーの最大Xサイズを決めておいて　HPバーの最大サイズ*余りをXのサイズに入れる？*/

	//プレイヤーのHealthをHpのx方向のサイズに設定
	m_playerHp = GetPlayer().GetStatus().Health;

	//プレイヤーHPのロード
	m_playerHpTexture.Load(L"Assets/sprite/hp2.png");
	m_playerHpSprite.Init(&m_playerHpTexture);
	m_playerHpSprite.SetCenterPosition({ m_playerHpCenterPos });
	m_playerHpSprite.SetPosition({ m_playerHpPos });
	m_playerHpSize.x = (float)m_playerHp;
	m_playerHpSprite.SetSize({m_playerHpSize.x * m_playerHpSizeUp, m_playerHpSize.y});
	
	//プレイヤーHPバックグラウンドのロード
	m_playerHpBackTexture.Load(L"Assets/sprite/hpBack.png");
	m_playerHpBackSprite.Init(&m_playerHpBackTexture);
	m_playerHpBackSprite.SetCenterPosition({ m_playerHpBackCenterPos });
	m_playerHpBackSprite.SetPosition({ m_playerHpBackPos });
	m_playerHpBackSize.x = (float)m_playerHp;
	m_playerHpBackSprite.SetSize({ m_playerHpBackSize.x * m_playerHpSizeUp,m_playerHpBackSize.y });

}

void CPlayerHp::Update()
{
	//プレイヤーのHpが変化したときにメンバ変数にプレイヤーHpを代入する
	if (m_playerHp != GetPlayer().GetStatus().Health)
	{
		//Hpが増えたときに背景のサイズも増やす
		if (m_playerHp < GetPlayer().GetStatus().Health)
		{
			m_playerHpBackSize.x = (float)GetPlayer().GetStatus().Health;
			m_playerHpBackSprite.SetSize({ m_playerHpSize.x * m_playerHpSizeUp, m_playerHpSize.y });
		}

		m_playerHpSize.x = (float)GetPlayer().GetStatus().Health;
		m_playerHpSprite.SetSize({ m_playerHpSize.x * m_playerHpSizeUp, m_playerHpSize.y });

		//プレイヤーHp更新
		m_playerHp = GetPlayer().GetStatus().Health;

	}

	//HPの背景を減らしていく処理
	if (m_playerHpSize.x >= m_playerHpBackSize.x) { return; }
	m_playerHpBackSize.x -= m_hpSubtractSpeed;
	m_playerHpBackSprite.SetSize({ m_playerHpBackSize.x * m_playerHpSizeUp,m_playerHpBackSize.y });
}

void CPlayerHp::Draw()
{
	m_playerHpBackSprite.Draw();
	m_playerHpSprite.Draw();
}
