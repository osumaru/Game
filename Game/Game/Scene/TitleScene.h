/*
*	タイトルシーンクラス
*/
#pragma once
class CTitleScene :public IGameObject
{
public:
	//コンストラクタ
	CTitleScene();
	//デストラクタ
	~CTitleScene();
	//trueが返されるまで繰り返し呼ばれる
	bool Start() override;

	//初期化
	void Init();

	//更新
	void Update() override;

	//遅延描画
	void AfterDraw() override;

private:
	CSprite			m_title;					//Title画面のスプライト
	CTexture		m_titleTexture;				//Title画面のテクスチャ


};

