/*
*	ダメージ数値表示クラス
*/

#pragma once


class CNumber;

class CDamegeNumber
{
public:
	//初期化
	void Init();

	//ダメージ計算
	//dmg	受けたダメージ
	void DamageCalculation(int dmg);

	//座標を設定
	//position	座標
	void SetPosition(const CVector2& position)
	{
		m_numPos = position;
	}

	enum EnDigit {
		enDigit_One,		//一の位
		enDigit_Ten,		//十の位
		enDigit_Hundred,	//百の位
		enDigit_Num			//位の数
	};

private:
	CNumber* m_number[EnDigit::enDigit_Num];	//数字のスプライト
	CVector2 m_numPos;							//座標
	CVector2 m_numSize;							//サイズ
};