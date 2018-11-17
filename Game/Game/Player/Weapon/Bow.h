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

	/*
	矢をリストから削除する関数
	it	矢のイテレーター
	*/
	void ArrowDelete(std::list<CPlayerArrow*>::iterator it);
private:
	std::list<CPlayerArrow*>			m_arrowList;							//弓矢のリスト
	CSprite								m_tag;									//サークルのスプライト
	CTexture							m_texture;								//サークルのテクスチャ
	bool								m_isZoom;								//弓用の視点に切り替えるかの判定をする変数

};