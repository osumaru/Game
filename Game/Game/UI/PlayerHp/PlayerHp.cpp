#include "stdafx.h"
#include "PlayerHp.h"
#include "../../Player/Player.h"

void CPlayerHp::Init()
{


	//プレイヤーのHealthをHpのx方向のサイズに設定
	m_playerHp = GetPlayer().GetStatus().Health;
	m_playerMaxHp = (float)GetPlayer().GetStatus().Health;

	//プレイヤーHPのロード
	m_playerHpTexture = TextureResource().LoadTexture(L"Assets/sprite/hp2.png");
	m_playerHpSprite.Init(m_playerHpTexture);
	m_playerHpSprite.SetCenterPosition({ m_playerHpCenterPos });
	m_playerHpSprite.SetPosition({ m_playerHpPos });
	m_playerHpSize.x = (float)(m_playerMaxHpSizeX*(GetPlayer().GetStatus().Health / m_playerMaxHp));
	m_playerHpSprite.SetSize({ m_playerHpSize.x, m_playerHpSize.y});
	
	//プレイヤーHPバックグラウンドのロード
	m_playerHpBackTexture = TextureResource().LoadTexture(L"Assets/sprite/hpBack.png");
	m_playerHpBackSprite.Init(m_playerHpBackTexture);
	m_playerHpBackSprite.SetCenterPosition({ m_playerHpBackCenterPos });
	m_playerHpBackSprite.SetPosition({ m_playerHpBackPos });
	m_playerHpBackSize.x = (float)(m_playerMaxHpSizeX*(GetPlayer().GetStatus().Health / m_playerMaxHp));
	m_playerHpBackSprite.SetSize({ m_playerHpBackSize.x,m_playerHpBackSize.y });

}

void CPlayerHp::Update()
{
	//最大HPが変化したらプレイヤーステータスから取得する
	if (m_playerMaxHp != GetPlayer().GetStatus().MaxHealth)
	{
		m_playerMaxHp = (float)GetPlayer().GetStatus().MaxHealth;
	}

	//プレイヤーのHpが変化したときにメンバ変数にプレイヤーHpを代入する
	if (m_playerHp != GetPlayer().GetStatus().Health)
	{
		//Hpが増えたときに背景のサイズも増やす
		if (m_playerHp < GetPlayer().GetStatus().Health)
		{
			m_playerHpBackSize.x = (float)(m_playerMaxHpSizeX*(GetPlayer().GetStatus().Health / m_playerMaxHp));
			m_playerHpBackSprite.SetSize({ m_playerHpBackSize.x, m_playerHpSize.y });
		}

		m_playerHpSize.x = (float)(m_playerMaxHpSizeX*(GetPlayer().GetStatus().Health / m_playerMaxHp));
		m_playerHpSprite.SetSize({ m_playerHpSize.x, m_playerHpSize.y });

		//プレイヤーHp更新
		m_playerHp = GetPlayer().GetStatus().Health;
	}

	//HPの背景を減らしていく処理
	if ((float)(m_playerMaxHpSizeX*(GetPlayer().GetStatus().Health / m_playerMaxHp)) <= m_playerHpBackSize.x)
	{
		m_playerHpBackSize.x -= m_hpSubtractSpeed;
		m_playerHpBackSprite.SetSize({ m_playerHpBackSize.x,m_playerHpBackSize.y });
	}
}

void CPlayerHp::AfterDraw()
{
	m_playerHpBackSprite.Draw();
	m_playerHpSprite.Draw();
}
