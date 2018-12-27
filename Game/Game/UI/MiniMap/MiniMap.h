/*
*	ミニマップクラス
*/

#pragma once

class IEnemy;

class CMiniMap : public IGameObject
{
public:
	//コンストラクタ
	CMiniMap();

	//デストラクタ
	virtual ~CMiniMap();

	//初期化
	void Init();

	//更新
	void Update();

	//描画
	void AfterDraw();

private:
	CSprite									m_miniMap;				//ミニマップ
	CTexture*								m_miniMapTexture;
	CSprite									m_playerIcon;			//プレイヤーアイコン
	CTexture*								m_playerIconTexture;
	std::vector<std::unique_ptr<CSprite>>	m_enemyIcon;			//エネミーアイコン
	CTexture*								m_enemyIconTexture;
	std::list<IEnemy*>*						m_enemyList;			//エネミーリスト
	CVector2								m_mapCenterPos;			//ミニマップの中心座標
};
