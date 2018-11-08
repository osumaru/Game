/*
*	数字クラス 
*/

#pragma once

class CNumber
{
public:
	//初期化
	//numPos  座標
	//numSize サイズ
	void Init(CVector2 numPos, CVector2 numSize);

	//描画
	void Draw();

	//表示する数値を設定
	//int  num  数値
	void SetNumber(int num)
	{
		m_num = num;
	}

	//座標を設定
	//pos	座標
	void SetPosition(CVector2 pos)
	{
		m_number[m_num].SetPosition(pos);
	}

	//Z値を設定
	//depth		Z値
	void SetDepthValue(float depth)
	{
		m_number[m_num].SetDepthValue(depth);
	}

	//アルファ値を設定
	//alpha		アルファ値
	void SetAlpha(float alpha)
	{
		m_number[m_num].SetAlpha(alpha);
	}

	//描画するかどうかを設定
	void SetIsDraw(bool isDraw)
	{
		m_number[m_num].SetIsDraw(isDraw);
	}

	//描画するかの判定を取得
	bool GetIsDraw()
	{
		return m_number[m_num].IsDraw();
	}

	enum EnNumber {
		enNumber_Zero,	//0
		enNumber_One,	//1
		enNumber_Two,	//2
		enNumber_Three,	//3
		enNumber_Four,	//4
		enNumber_Five,	//5
		enNumber_Six,	//6
		enNumber_Seven,	//7
		enNumber_Eight,	//8
		enNumber_Nine,	//9
		enNumber_Num	//数字の数
	};

private:
	CSprite		m_number[EnNumber::enNumber_Num];			//スプライト
	CTexture	m_numberTexture[EnNumber::enNumber_Num];	//テクスチャ
	int			m_num = 0;									//数値を保存する変数
};