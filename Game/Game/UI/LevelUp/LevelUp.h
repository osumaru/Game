#pragma once
class CLevelUp : public IGameObject
{
public:
	CLevelUp();
	~CLevelUp();

	//初期化
	void Init();

	//更新
	void Update();

	//描画
	void PostAfterDraw();

private:
	CSprite			m_playerLevelUpSprite;							//プレイヤーレベルアップスプライト
	CTexture*		m_playerLevelUpTexture;							//プレイヤーレベルアップテクスチャ
	const CVector2	m_playerLevelUpPos = {0.0f,10.0f };			//プレイヤーレベルアップ座標
	CVector2		m_playerLevelUpSize = { 200.0f,200.0f };			//プレイヤーレベルアップサイズ
	float			m_playerLevelUpAlpha = 0.0f;
	int				m_playerLevelValue = 1;
};

