/*
*	侍クラス
*/

#pragma once

#include "Enemy/IEnemy.h"

class CSamurai : public IEnemy
{
public:
	//コンストラクタ
	CSamurai();

	//デストラクタ
	~CSamurai();

	//初期化
	//position	座標
	void Init(const CVector3& position) override;

	//更新される前に一度だけ呼ばれる
	bool Start();

	//更新
	void Update();

	//描画
	void Draw();

	//攻撃
	void Attack();

	void OnInvokeAnimationEvent(const wchar_t* animClipName, const wchar_t* eventName)override;
};