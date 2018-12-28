/*
*	ゲームシーンクラス
*/
#pragma once
class CClearScene :
	public IGameObject
{
public:
	//コンストラクタ
	CClearScene();
	//デストラクタ
	~CClearScene();
	//trueが返されるまで繰り返し呼ばれる
	bool Start() override;
	//更新
	void Update() override;
	//遅延描画
	void AfterDraw() override;

private:
	CSprite			m_clear;					//Clear画面のスプライト
	CTexture*		m_clearTexture;				//Clear画面のテクスチャ
};

