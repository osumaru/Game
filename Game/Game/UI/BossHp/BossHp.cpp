#include "stdafx.h"
#include "BossHp.h"
#include "../../Enemy/Maw.h"


void CBossHp::Init()
{
	//HealthをHpのx方向のサイズに設定
	m_bossHp = GetMaw().GetSmawStatus().Hp;
	m_bossMaxHp = (float)GetMaw().GetSmawStatus().Hp;

	//HPのロード
	m_bossHpTexture = TextureResource().LoadTexture(L"Assets/sprite/BossHP.png");
	m_bossHpSprite.Init(m_bossHpTexture);
	m_bossHpSprite.SetCenterPosition({ m_bossHpCenterPos });
	m_bossHpSprite.SetPosition({ m_bossHpPos });
	m_bossHpSize.x = (float)(m_bossMaxHpSizeX*(GetMaw().GetSmawStatus().Hp / m_bossMaxHp));
	m_bossHpSprite.SetSize({ m_bossHpSize.x, m_bossHpSize.y });

	//HPバックグラウンドのロード
	m_bossHpBackTexture = TextureResource().LoadTexture(L"Assets/sprite/BossHPBack.png");
	m_bossHpBackSprite.Init(m_bossHpBackTexture);
	m_bossHpBackSprite.SetCenterPosition({ m_bossHpBackCenterPos });
	m_bossHpBackSprite.SetPosition({ m_bossHpBackPos });
	m_bossHpBackSize.x = (float)(m_bossMaxHpSizeX*(GetMaw().GetSmawStatus().Hp / m_bossMaxHp));
	m_bossHpBackSprite.SetSize({ m_bossHpBackSize.x,m_bossHpBackSize.y });

	//HPバックグラウンドのロード
	m_bossHpFrameTexture = TextureResource().LoadTexture(L"Assets/sprite/BossHPFrame.png");
	m_bossHpFrameSprite.Init(m_bossHpFrameTexture);
	m_bossHpFrameSprite.SetCenterPosition({ m_bossHpFrameCenterPos });
	m_bossHpFrameSprite.SetPosition({ m_bossHpFramePos });
	m_bossHpFrameSize.x = (float)(m_bossMaxHpSizeX + 30.0f);
	m_bossHpFrameSprite.SetSize({ m_bossHpFrameSize.x,m_bossHpFrameSize.y });

	//this->SetIsActive(false);
}

void CBossHp::Update()
{
	//if (GetMaw().) { return; }
	//最大HPが変化したらステータスから取得する
	if (m_bossMaxHp != GetMaw().GetSmawStatus().MaxHp)
	{
		m_bossMaxHp = (float)GetMaw().GetSmawStatus().MaxHp;
	}

	//Hpが変化したときにメンバ変数にプレイヤーHpを代入する
	if (m_bossHp != GetMaw().GetSmawStatus().Hp)
	{
		//Hpが増えたときに背景のサイズも増やす
		if (m_bossHp < GetMaw().GetSmawStatus().Hp)
		{
			m_bossHpBackSize.x = (float)(m_bossMaxHpSizeX*(GetMaw().GetSmawStatus().Hp / m_bossMaxHp));
			m_bossHpBackSprite.SetSize({ m_bossHpBackSize.x, m_bossHpSize.y });
		}

		m_bossHpSize.x = (float)(m_bossMaxHpSizeX*(GetMaw().GetSmawStatus().Hp / m_bossMaxHp));
		m_bossHpSprite.SetSize({ m_bossHpSize.x, m_bossHpSize.y });

		//Hp更新
		m_bossHp = GetMaw().GetSmawStatus().Hp;
	}

	//HPの背景を減らしていく処理
	if ((float)(m_bossMaxHpSizeX*(GetMaw().GetSmawStatus().Hp / m_bossMaxHp)) <= m_bossHpBackSize.x)
	{
		m_bossHpBackSize.x -= m_hpSubtractSpeed;
		m_bossHpBackSprite.SetSize({ m_bossHpBackSize.x,m_bossHpBackSize.y });
	}
}

void CBossHp::PostAfterDraw()
{
	m_bossHpFrameSprite.Draw();
	m_bossHpBackSprite.Draw();
	m_bossHpSprite.Draw();
}
