#pragma once

class CPlayerHp : public IGameObject
{
public:
	//初期化
	void Init();

	//更新
	void Update();

	//描画
	void Draw();

	//プレイヤーHP
	//DamageValue くらったダメージ量0〜100
	//void PlayerDamage(float DamageValue);
private:
	CSprite m_playerHpSprite;							//プレイヤーのHPスプライト
	CTexture m_playerHpTexture;							//プレイヤーのHPテクスチャ
	const CVector2 m_playerHpPos = {-620.0f,270.0f};	//プレイヤーのHP座標
	CVector2 m_playerHpSize = {300.0f,60.0f};			//プレイヤーのHPサイズ
	const CVector2 m_playerHpCenterPos = { 0.0f,1.0f };	//プレイヤーのHP基点座標
	float m_hpSubtractSpeed = 1.0f;						//プレイヤーのHPが減少する速度

	CSprite m_playerHpBackSprite;							//プレイヤーのHPバックグラウンドスプライト
	CTexture m_playerHpBackTexture;							//プレイヤーのHPバックグラウンドテクスチャ
	const CVector2 m_playerHpBackPos = { -620.0f,270.0f };	//プレイヤーのHPバックグラウンド座標
	CVector2 m_playerHpBackSize = { 300.0f,60.0f };			//プレイヤーのHPバックグラウンドサイズ
	const CVector2 m_playerHpBackCenterPos = { 0.0f,1.0f };	//プレイヤーのHPバックグラウンド基点座標

	int m_playerHp=100;										//プレイヤーのHPの値
};

