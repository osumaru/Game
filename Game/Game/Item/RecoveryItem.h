/*
*	回復アイテムクラス
*/

#pragma once

#include "IItem.h"

class CRecoveryItem : public IItem
{
public:
	//初期化
	//position	座標
	void Init();

	//更新する前に一度だけ呼ばれる
	bool Start() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//アイテムを使う
	void Use() override;

	//ポップさせる
	void Pop(CVector3 position);

private:
	int m_recoveryValue = 30;	//回復値
};
