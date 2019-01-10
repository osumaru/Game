#pragma once
class CResult: public IGameObject
{
public:
	CResult();
	~CResult();
	void Init();
	void Update();
	void Draw();
	void AfterDraw();

	//描画されたか
	bool GetDraw()
	{
		return m_isDraw;
	}
private:
	CSprite			m_result;						//Result画面のスプライト
	CTexture*		m_resultTexture;				//Result画面のテクスチャ
	float			m_alphaTime = 0.0f;
	bool			m_isDraw = false;	//描画されたか
};

