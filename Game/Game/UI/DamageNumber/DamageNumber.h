/*
*	ダメージ数値表示クラス
*/

#pragma once


class CPlayer;
class CEnemy;

#include "Number.h"

class CDamegeNumber
{
public:
	//初期化
	void Init();

	//ダメージ計算
	//player	プレイヤークラスのポインタ
	//enemy		エネミークラスのポインタ

	void DamageCalculation(CPlayer* player, CEnemy* enemy);


private:
	CNumber* m_number[3];	//数字のスプライト
	Vector2 m_numPos;		//座標
	Vector2 m_numSize;		//サイズ
};