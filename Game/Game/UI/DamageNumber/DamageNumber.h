/*
*	ダメージ数値表示クラス
*/

#pragma once

class CPlayer;
class Enemy;
#include "Number.h"

class DamegeNumber
{
public:
	//初期化
	void Init();

	//ダメージ計算
	//player	プレイヤークラスのポインタ
	//enemy		エネミークラスのポインタ
	void DamageCalculation(CPlayer* player, Enemy* enemy);

private:
	Number* m_number[3];	//数字のスプライト
	Vector2 m_numPos;		//座標
	Vector2 m_numSize;		//サイズ
};