#pragma once
class CWeekPoint :
	public IGameObject
{
public:
	//初期化
	void Init();
	//更新
	void Update() override;
	//描画
	void Draw() override;

	void PostAfterDraw() override;
private:
	CSprite						m_weekSprite;		//弱点のスプライト
	CTexture*					m_weekTexture;		//弱点のテクスチャ
};

