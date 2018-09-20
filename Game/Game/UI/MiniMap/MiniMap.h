/*
*	ミニマップクラス
*/

#pragma once

class CMiniMap : public IGameObject
{
public:
	//初期化
	void Init();

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

	CSprite m_enemyIcon;						//プレイヤーアイコン
	CTexture m_enemyIconTexture;
	CVector3 m_enemyIconVec = CVector3::AxisZ;	//プレイヤーアイコンの向き
};
