/*
*	ウォーロッククラス
*/

#pragma once

#include "Enemy/IEnemy.h"

class CWarrok : public IEnemy
{
public:
	//コンストラクタ
	CWarrok();

	//デストラクタ
	~CWarrok();

	//初期化
	//position	座標
	void Init(CVector3 position) override;

	//更新される前に一度だけ呼ばれる
	bool Start();

	//更新
	void Update();

	//描画
	void Draw();

	//攻撃
	void Attack() override;

	void OnInvokeAnimationEvent(const wchar_t* animClipName, const wchar_t* eventName)override;
};