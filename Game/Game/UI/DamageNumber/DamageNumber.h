/*
*	ダメージ数値表示クラス
*/

#pragma once

#include "Number.h"

class CDamageNumber : public IGameObject
{
public:
	//初期化
	void Init();

	//更新
	void Update() override;

	//描画
	void AfterDraw() override;

	//ダメージ計算
	//dmg	受けたダメージ
	void DamageCalculation(int dmg);

	//座標を設定
	//position	座標
	void SetPosition(const CVector2& position);

	enum EnDigit {
		enDigit_One,		//一の位
		enDigit_Ten,		//十の位
		enDigit_Hundred,	//百の位
		enDigit_Num			//位の数
	};

private:
	CNumber  m_number[EnDigit::enDigit_Num];	//数字のスプライト
	CVector2 m_numPos;							//座標
	CVector2 m_numSize;							//サイズ
	float    m_timer = 0.0f;					//タイマー
	float    m_alphaTime = 0.0f;				//アルファ値を計算するための時間
	const float m_drawTime = 1.0f;				//描画している時間
};