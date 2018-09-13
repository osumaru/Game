#pragma once
class CResult: public IGameObject
{
public:
	CResult();
	~CResult();
	void Init();
	void Update();
	void Draw();

private:
	CSprite			m_result;					//Result画面のスプライト
	CTexture		m_resultTexture;				//Result画面のテクスチャ
	
};

