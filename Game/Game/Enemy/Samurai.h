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
	//level		レベル
	void Init(const CVector3& position, int level) override;

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