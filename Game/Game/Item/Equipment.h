/*
*	装備アイテムクラス
*/

#pragma once

#include "IItem.h"

class CEquipment : public IItem
{
public:
	//初期化
	void Init();

	//更新する前に一度だけ呼ばれる
	bool Start() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//ポップさせる
	//position		座標
	void Pop(CVector3 position);
private:
	////装備のパラメーター
	//struct SEquipParameter
	//{
	//	int hp;			//HP
	//	int	strength;	//攻撃力
	//	int defense;	//防御力
	//};

	//SEquipParameter m_equipParameter;
};