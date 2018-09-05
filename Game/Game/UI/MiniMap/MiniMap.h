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
	CSprite m_miniMap;				//ミニマップ
	CTexture m_miniMapTexture;

	CSprite m_playerIcon;			//プレイヤーアイコン
	CTexture m_playerIconTexture;
	CVector3 m_playerFowardOld;
};
