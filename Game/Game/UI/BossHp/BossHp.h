#pragma once
class CBossHp : public IGameObject
{
public:
	//初期化
	void Init();

	//更新
	void Update();

	//描画
	void AfterDraw();

private:
	CSprite			m_bossHpSprite;							//ボスのHPスプライト
	CTexture*		m_bossHpTexture;						//ボスのHPテクスチャ
	const CVector2	m_bossHpPos = { 420.0f,270.0f };		//ボスのHP座標
	CVector2		m_bossHpSize = { 300.0f,40.0f };		//ボスのHPサイズ
	const CVector2	m_bossHpCenterPos = { 1.0f,1.0f };		//ボスのHP基点座標
	float			m_hpSubtractSpeed = 1.0f;				//ボスのHPが減少する速度

	CSprite			m_bossHpBackSprite;						//ボスのHPバックグラウンドスプライト
	CTexture*		m_bossHpBackTexture;					//ボスのHPバックグラウンドテクスチャ
	const CVector2	m_bossHpBackPos = { 420.0f,270.0f };	//ボスのHPバックグラウンド座標
	CVector2		m_bossHpBackSize = { 300.0f,40.0f };	//ボスのHPバックグラウンドサイズ
	const CVector2	m_bossHpBackCenterPos = { 1.0f,1.0f };	//ボスのHPバックグラウンド基点座標

	int				m_bossHp = 0;							//ボスのHPの値
	//int				m_bossHpSizeUp = 3;						//ボスのHPの大きさを調整する用の変数
	float			m_bossMaxHp = 0;						//ボスの最大Hp
	float			m_bossMaxHpSizeX = 400.0f;				//ボスの最大X方向の大きさ
};

