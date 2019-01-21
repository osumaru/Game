/*
*	ゾンビクラス
*/

#pragma once

#include "Enemy/IEnemy.h"

class CZombie : public IEnemy
{
public:
	//コンストラクタ
	CZombie();

	//デストラクタ
	~CZombie();

	//初期化
	//position	座標
	void Init(const CVector3& position) override;

	//更新される前に一度だけ呼ばれる
	bool Start() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//攻撃
	void Attack() override;

	void OnInvokeAnimationEvent(const wchar_t* animClipName, const wchar_t* eventName)override;
};