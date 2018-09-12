/*
*	数字クラス 
*/

#pragma once

class CNumber : public IGameObject
{
public:
	//初期化
	//Vector2  numPos  座標
	//Vector2  numSize サイズ
	void Init(CVector2 numPos, CVector2 numSize);

	//更新
	void Update();

	//描画
	void Draw();

	//表示する数値を設定
	//int  num  数値
	void SetNumber(int num);
private:
	CSprite		m_number[10];			//スプライト
	CTexture	m_numberTexture[10];	//テクスチャ
	int			m_num = 0;				//数値を保存する変数
};