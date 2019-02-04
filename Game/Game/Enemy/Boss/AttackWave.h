/*
*	ボスの攻撃で発生する波クラス
*/

#pragma once

class CCamera;

class CAttackWave : public IGameObject
{
public:
	//初期化
	//camera	カメラ
	//position	座標
	void Init(const CCamera* camera, const CVector3& position);

	//更新
	void Update() override;

private:
	CEffect		m_rippleEffect;					//エフェクト					
	CVector3	m_position;						//座標
	const float	WAVE_WIDTH = 1.0f;				//波の幅
	float		m_waveHitLength = WAVE_WIDTH;	//波が当たる距離
	float		m_timer = 0.0f;					//タイマー
};