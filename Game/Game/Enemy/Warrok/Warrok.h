/*
*	ウォーロッククラス
*/

#pragma once

#include "Enemy/IEnemy.h"

class CRock;

class CWarrok : public IEnemy
{
public:
	//コンストラクタ
	CWarrok();

	//デストラクタ
	~CWarrok();

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

	//岩で攻撃するときに回転させる
	void RockAttackRotation();

	//アニメーションイベントが呼ばれるときに呼ばれる
	//animClipName		アニメーションのファイル名
	void OnInvokeAnimationEvent(const wchar_t* animClipName, const wchar_t* eventName)override;

private:
	CRock*	m_rock = nullptr;	//岩
};