#pragma once

class Map;
class CWeaponSelect;
class CPlayerHp;
class CLevelUp;
class CMenu;
class CResult;
class CGameSound;
class CMessage;
class CChoices;
class CArrowRemain;

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

	//メニューの取得
	CMenu* GetMenu()
	{
		return m_menu;
	}

private:
	Map*			m_map = nullptr;			//マップ
	CWeaponSelect*	m_weaponSelect = nullptr;	//武器選択
	CPlayerHp*		m_playerHp = nullptr;		//プレイヤーHP
	CLevelUp*		m_levelUp = nullptr;		//レベルアップ表示
	CMenu*			m_menu = nullptr;			//メニュー
	CResult*		m_result = nullptr;			//リザルト
	CGameSound*		m_gameSound = nullptr;		//ゲームサウンド
	CMessage*		m_message = nullptr;		//メッセージ表示
	CChoices*		m_choices = nullptr;		//選択肢表示
	CArrowRemain*	m_arrowRemain = nullptr;	//矢の残弾数
};