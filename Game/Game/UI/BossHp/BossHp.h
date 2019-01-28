#pragma once
class CBossHp : public IGameObject
{
public:
	//初期化
	void Init();

	//更新
	void Update();

	//描画
	void PostAfterDraw();

private:
	CSprite			m_bossHpSprite;							//ボスのHPスプライト
	CTexture*		m_bossHpTexture;						//ボスのHPテクスチャ
	const CVector2	m_bossHpPos = { -400.0f,-250.0f };		//ボスのHP座標
	CVector2		m_bossHpSize = { 300.0f,100.0f };		//ボスのHPサイズ
	const CVector2	m_bossHpCenterPos = { 0.0f,0.0f };		//ボスのHP基点座標
	float			m_hpSubtractSpeed = 1.0f;				//ボスのHPが減少する速度

	CSprite			m_bossHpBackSprite;						//ボスのHPバックグラウンドスプライト
	CTexture*		m_bossHpBackTexture;					//ボスのHPバックグラウンドテクスチャ
	const CVector2	m_bossHpBackPos = { -400.0f,-250.0f };	//ボスのHPバックグラウンド座標
	CVector2		m_bossHpBackSize = { 300.0f,100.0f };	//ボスのHPバックグラウンドサイズ
	const CVector2	m_bossHpBackCenterPos = { 0.0f,0.0f };	//ボスのHPバックグラウンド基点座標

	CSprite			m_bossHpFrameSprite;						//ボスのHPバックグラウンドスプライト
	CTexture*		m_bossHpFrameTexture;					//ボスのHPバックグラウンドテクスチャ
	const CVector2	m_bossHpFramePos = { -415.0f,-235.0f };	//ボスのHPバックグラウンド座標
	CVector2		m_bossHpFrameSize = { 380.0f,130.0f };	//ボスのHPバックグラウンドサイズ
	const CVector2	m_bossHpFrameCenterPos = { 0.0f,0.0f };	//ボスのHPバックグラウンド基点座標

	int				m_bossHp = 0;							//ボスのHPの値
	//int				m_bossHpSizeUp = 3;						//ボスのHPの大きさを調整する用の変数
	float			m_bossMaxHp = 0;						//ボスの最大Hp
	float			m_bossMaxHpSizeX = 1000.0f;				//ボスの最大X方向の大きさ
};

