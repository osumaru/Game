/*
*	タイトルシーンクラス
*/
#pragma once

class Map;
class CGameSound;

class CTitleScene :public IGameObject
{
public:
	//コンストラクタ
	CTitleScene();
	//デストラクタ
	~CTitleScene();
	//trueが返されるまで繰り返し呼ばれる
	bool Start() override;

	//更新
	void Update() override;

	//遅延描画
	void AfterDraw() override;

	//死ぬ前に呼びだされる
	void BeforeDead() override;
private:
	Map*		m_map = nullptr;		//マップ
	CGameSound*	m_gameSound = nullptr;	//ゲームサウンド
	CSprite		m_title;				//タイトル
	CSprite		m_start;				//スタート
	float		m_timer = 0.0f;			//タイマー
	const float ALPHA_TIME = 2.0f;		//透明になるまでの時間
	bool		m_isNoColor = false;	//透明になっているか
};

