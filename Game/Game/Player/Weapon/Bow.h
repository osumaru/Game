#pragma once
#include "IWeapon.h"
class CPlayerArrow;
//矢を撃つ弓クラス

class CBow : public IWeapon
{
public:

	~CBow();

	void Init()override;

	void Update()override;

	void AfterDraw()override;

	//矢を作る関数
	void ArrowCreate();

	void Release();

	/*
	矢をリストから削除する関数
	it	矢のイテレーター
	*/
	void ArrowDelete(std::list<CPlayerArrow*>::iterator it);

	//残弾数を取得
	int GetRemainNum()
	{
		return m_remainNum;
	}

private:
	std::list<CPlayerArrow*>			m_arrowList;							//弓矢のリスト
	CSprite								m_tag;									//サークルのスプライト
	CTexture*							m_texture;								//サークルのテクスチャ
	bool								m_isZoom;								//弓用の視点に切り替えるかの判定をする変数
	float								m_timer = 0.0f;					//タイマー
	float								RECOVERY_TIME = 10.0f;			//弾が回復する時間
	int									ARROW_LIMIT_NUM = 5;			//弾数の限界
	int									m_remainNum = ARROW_LIMIT_NUM;	//残弾数
};