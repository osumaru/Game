/*
*	プレイヤーのワイヤー移動クラス
*/

#pragma once

#include "PlayerState.h"

class CPlayerWireMove : public IPlayerState
{
public:
	//コンストラクタ
	CPlayerWireMove();

	//デストラクタ
	~CPlayerWireMove() {}

	void Init()override;

	//更新
	void Update()override;

	//ワイヤー描画を更新
	void UpdateWireDraw();

private:
	CEffect		m_hitEffect;
	CVector3	m_movePosition;		//移動先の座標
	const float m_speed = 40.0f;	//移動速度
	float		m_accel = 0.0f;
	float		m_moveSpeed = 0.0f;
	bool		m_isWireThrow = true;	//ワイヤーを投げているか
	const CMatrix*	m_playerHandMatrix;	//プレイヤーの手のワールド行列
	CVector3	m_playerHandPos = CVector3::Zero; //プレイヤーの手の座標
	float		m_wireSpeed = 1.0f;		//ワイヤーを投げるスピード
	CVector3	m_moveDirection;	//前のフレームの移動速度
	CSoundSource* m_windSound = nullptr;//風の音
};