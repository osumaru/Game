/*
*	ゲームシーンクラス
*/

#pragma once
class Map;
class CWeaponSelect;
class CMiniMap;
class CPlayerHp;
class CLevelUp;
class CMenu;
class CResult;
class CGameSound;

class CGameScene : public IGameObject
{
public:

	//開放
	void Release();

	//初期化
	void Init();

	//更新
	void Update() override;

	//マップの取得
	Map* GetMap()
	{
		return m_map;
	}

	//武器選択の取得
	CWeaponSelect*	GetWeaponSelect()
	{
		return m_weaponSelect;
	}

	CGameSound* GetGameSound()
	{
		return m_gameSound;
	}

private:
	Map*			m_map = nullptr;			//マップ
	CWeaponSelect*	m_weaponSelect = nullptr;	//武器選択
	CMiniMap*		m_miniMap = nullptr;		//ミニマップ
	CPlayerHp*		m_playerHp = nullptr;		//プレイヤーHP
	CLevelUp*		m_levelUp = nullptr;		//レベルアップ表示
	CMenu*			m_menu = nullptr;			//メニュー
	CResult*		m_result = nullptr;			//リザルト
	CGameSound*		m_gameSound = nullptr;		//ゲームサウンド
};
