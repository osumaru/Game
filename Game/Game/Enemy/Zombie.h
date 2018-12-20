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
	void Init(CVector3 position) override;

	//更新される前に一度だけ呼ばれる
	bool Start();

	//更新
	void Update();

	//描画
	void Draw();

	void OnInvokeAnimationEvent(const wchar_t* animClipName, const wchar_t* eventName)override;
};