#include "AttackWave.h"
#include "../../Player/Player.h"
#include "Maw.h"
#include "../../Scene/SceneManager.h"

void CAttackWave::Init(const CCamera* camera, const CVector3& position)
{
	//エフェクトの初期化
	m_rippleEffect.Init(L"Assets/Effect/rippleEffect.efk");
	m_rippleEffect.SetScale({ 1.0f,1.0f,1.0f });
	m_rippleEffect.SetPosition(position);
	m_rippleEffect.Play();
	m_rippleEffect.Update();
	//座標を設定
	m_position = position;
}

void CAttackWave::Update()
{
	const float LIFE_TIME = 0.6f;
	m_timer += GameTime().GetDeltaFrameTime();
	if (m_timer > LIFE_TIME || GetSceneManager().GetSceneChange() || GetPlayer().GetIsDied())
	{
		Delete(this);
	}
	const float WAVE_SPEED = 10.0f;	//波のスピード
	//プレイヤーとの当たり判定をとる
	CVector3 distance = GetPlayer().GetPosition() - m_position;
	float length = distance.Length();
	if (length < m_waveHitLength)
	{
		if (length > m_waveHitLength - WAVE_WIDTH &&
			GetPlayer().GetCharacterController().IsOnGround())
		{
			//プレイヤーに当たった
			GetPlayer().SetDamage(GetMaw().GetSmawStatus().Strength);
			GetPlayer().SetDamageEnemyPos(m_position);
		}
	}
	m_waveHitLength += WAVE_SPEED * GameTime().GetDeltaFrameTime();
}