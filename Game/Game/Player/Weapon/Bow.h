#pragma once
#include "IWeapon.h"
class CPlayerArrow;

class CBow : public IWeapon
{
public:

	~CBow();

	void Init()override;

	void Update()override;

	void AfterDraw()override;

	void ArrowCreate();

	void ArrowDelete(std::list<CPlayerArrow*>::iterator it);
private:
	std::list<CPlayerArrow*>			m_arrowList;							//弓矢のリスト
	CSprite								m_tag;								//サークルのスプライト
	CTexture							m_texture;
	bool								m_isZoom;								//弓用の視点に切り替えるかの判定をする変数

};