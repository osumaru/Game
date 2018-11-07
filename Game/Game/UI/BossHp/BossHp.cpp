#include "stdafx.h"
#include "BossHp.h"
#include "../Game/Enemy/Maw.h"

CBossHp::CBossHp()
{
}


CBossHp::~CBossHp()
{
}

void CBossHp::Init()
{
	//プレイヤーのHealthをHpのx方向のサイズに設定
	m_bossHp = GetMaw().GetSmawStatus().Hp;
	m_bossMaxHp = (float)GetMaw().GetSmawStatus().Hp;

	//プレイヤーHPのロード
	m_bossHpTexture.Load(L"Assets/sprite/hp2.png");
	m_bossHpSprite.Init(&m_bossHpTexture);
	m_bossHpSprite.SetCenterPosition({ m_bossHpCenterPos });
	m_bossHpSprite.SetPosition({ m_bossHpPos });
	m_bossHpSize.x = (float)(m_bossMaxHpSizeX*(GetMaw().GetSmawStatus().Hp / m_bossMaxHp));
	m_bossHpSprite.SetSize({ m_bossHpSize.x, m_bossHpSize.y });

	//プレイヤーHPバックグラウンドのロード
	m_bossHpBackTexture.Load(L"Assets/sprite/hpBack.png");
	m_bossHpBackSprite.Init(&m_bossHpBackTexture);
	m_bossHpBackSprite.SetCenterPosition({ m_bossHpBackCenterPos });
	m_bossHpBackSprite.SetPosition({ m_bossHpBackPos });
	m_bossHpBackSize.x = (float)(m_bossMaxHpSizeX*(GetMaw().GetSmawStatus().Hp / m_bossMaxHp));
	m_bossHpBackSprite.SetSize({ m_bossHpBackSize.x,m_bossHpBackSize.y });

}

void CBossHp::Update()
{
	//最大HPが変化したらプレイヤーステータスから取得する
	if (m_bossMaxHp != GetMaw().GetSmawStatus().MaxHp)
	{
		m_bossMaxHp = (float)GetMaw().GetSmawStatus().MaxHp;
	}

	//プレイヤーのHpが変化したときにメンバ変数にプレイヤーHpを代入する
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

		//プレイヤーHp更新
		m_bossHp = GetMaw().GetSmawStatus().Hp;
	}

	//HPの背景を減らしていく処理
	if ((float)(m_bossMaxHpSizeX*(GetMaw().GetSmawStatus().Hp / m_bossMaxHp)) <= m_bossHpBackSize.x)
	{
		m_bossHpBackSize.x += m_hpSubtractSpeed;
		m_bossHpBackSprite.SetSize({ m_bossHpBackSize.x,m_bossHpBackSize.y });
	}
}

void CBossHp::AfterDraw()
{
	m_bossHpBackSprite.Draw();
	m_bossHpSprite.Draw();
}
