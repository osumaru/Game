/*
*	ミニマップクラス
*/

#pragma once

class IEnemy;

class CMiniMap : public IGameObject
{
public:
	//初期化
	//enemyNum		敵の数
	void Init(std::list<IEnemy*> enemyList);

	//更新
	void Update();

	//描画
	void Draw();

private:
	CSprite m_miniMap;							//ミニマップ
	CTexture m_miniMapTexture;

	CSprite m_playerIcon;						//プレイヤーアイコン
	CTexture m_playerIconTexture;
	CVector3 m_playerIconVec = CVector3::AxisZ;	//プレイヤーアイコンの向き

	CCamera m_camera;

	std::list<CSprite> m_enemyIconList;
	CTexture m_enemyIconTexture;

	std::list<IEnemy*> m_enemyList;

	CVector2 m_mapCenterPos;
};
