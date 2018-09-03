#pragma once

class PlayerHp : public IGameObject
{
public:
	//初期化
	void Init();

	//更新
	void Update();

	//描画
	void Draw();
private:
	CSprite m_playerHpSprite;		//プレイヤーのHPスプライト
	CTexture m_playerHpTexture;		//プレイヤーのHPテクスチャ
	const CVector2 m_playerHpPos = {-400.0f,300.0f};	//プレイヤーのHP座標
	const CVector2 m_playerHpSize = {450.0f,100.0f};	//プレイヤーのHPサイズ
};

