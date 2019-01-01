#pragma once

class Map;
class CWeaponSelect;
class CMiniMap;
class CPlayerHp;
class CLevelUp;
class CMenu;
class CResult;
class CGameSound;

class CBossScene : public IGameObject
{
public:
	//コンストラクタ
	CBossScene() {};

	//デストラクタ
	~CBossScene() {};

	//更新される前に一度だけ呼ばれる
	bool Start() override;

	//更新
	void Update() override;

	//死ぬ前に呼び出される
	void BeforeDead() override;

	//マップの取得
	Map* GetMap()
	{
		return m_map;
	}
private:
	Map*			m_map = nullptr;			//マップ
	CWeaponSelect*	m_weaponSelect = nullptr;	//武器選択
	CPlayerHp*		m_playerHp = nullptr;		//プレイヤーHP
	CLevelUp*		m_levelUp = nullptr;		//レベルアップ表示
	CMenu*			m_menu = nullptr;			//メニュー
	CResult*		m_result = nullptr;			//リザルト
	CGameSound*		m_gameSound = nullptr;		//ゲームサウンド
};