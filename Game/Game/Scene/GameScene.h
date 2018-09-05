/*
*	ゲームシーンクラス
*/

#pragma once

class Map;
#include "../UI/DamageNumber/DamageNumber.h"

class CGameScene : public IGameObject
{
public:
	//初期化
	void Init();

	//更新
	void Update();

private:
	Map* map = nullptr;			//マップ
	CDamegeNumber damageNumber;	//ダメージ数値
};