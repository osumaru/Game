#pragma once
#include "PlayerState.h"

class CPlayerAvoidance: public IPlayerState
{
public:
	//初期化
	void Init()override;

	//更新処理
	void Update()override;

	//移動処理
	void Move();

	//回転
	void Rotation();
private:
	const CMatrix* m_pBoneMat;	//ボーンの行列のポインタ
	float	m_fallSpeed = 0.0f;
};

