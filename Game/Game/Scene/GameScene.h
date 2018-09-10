/*
*	ゲームシーンクラス
*/

#pragma once

class Map;

class CGameScene : public IGameObject
{
public:
	//初期化
	void Init();

	//更新
	void Update();

private:
	Map* map = nullptr;			//マップ
};