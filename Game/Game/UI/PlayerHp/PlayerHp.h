#pragma once

class PlayerHp : public GameObject
{
public:
	//初期化
	void Init();

	//更新
	void Update();

	//描画
	void Draw();
private:
	Sprite m_playerHpSprite;		//プレイヤーのHPスプライト
	Texture m_playerHpTexture;		//プレイヤーのHPテクスチャ
	const Vector2 m_playerHpPos = {-400.0f,300.0f};	//プレイヤーのHP座標
	const Vector2 m_playerHpSize = {450.0f,100.0f};	//プレイヤーのHPサイズ
};

