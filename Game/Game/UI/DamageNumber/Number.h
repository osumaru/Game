/*
*	数字クラス 
*/

#pragma once

class CNumber : public IGameObject
{
public:
	//初期化
	//numPos  座標
	//numSize サイズ
	void Init(CVector2 numPos, CVector2 numSize);

	//更新
	void Update();

	//描画
	void Draw();

	//表示する数値を設定
	//int  num  数値
	void SetNumber(int num);

	void SetPosition(CVector2 pos)
	{
		m_number[m_num].SetPosition(pos);
	}

	void SetDepthValue(float depth)
	{
		m_number[m_num].SetDepthValue(depth);
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