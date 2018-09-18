/*
*	ゲームシーンクラス
*/

#pragma once

class Map;
class CWeaponSelect;

class CGameScene : public IGameObject
{
public:
	//初期化
	void Init();

	//更新
	void Update();

	Map* GetMap()
	{
		return map;
	}

	CWeaponSelect*	GetWeaponSelect()
	{
		return m_weaponSelect;
	}

private:
	Map* map = nullptr;			//マップ
	CWeaponSelect* m_weaponSelect = nullptr;
};
