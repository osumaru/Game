/*
*	数字クラス 
*/

#pragma once

class Number : public GameObject
{
public:
	//初期化
	//Vector2  numPos  座標
	//Vector2  numSize サイズ
	void Init(Vector2 numPos, Vector2 numSize);

	//更新
	void Update();

	//描画
	void Draw();

	//表示する数値を設定
	//int  num  数値
	void SetNumber(int num);
private:
	Sprite	m_number[10];			//スプライト
	Texture m_numberTexture[10];	//テクスチャ
	int		m_num = 0;				//数値を保存する変数
};