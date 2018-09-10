/*
*	ダメージ数値表示クラス
*/

#pragma once


class CPlayer;

#include "Number.h"

class CDamegeNumber
{
public:
	//初期化
	void Init();

	//ダメージ計算
	void DamageCalculation();

	//ダメージ表示リセット
	void Reset();
private:
	CNumber* m_number[3];	//数字のスプライト
	CVector2 m_numPos;		//座標
	CVector2 m_numSize;		//サイズ
};