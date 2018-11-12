#pragma once
class INpcState	:	public IGameObject
{
public:
	INpcState();
	~INpcState();
	virtual void Init(const CVector3 position, const CQuaternion rotation) = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	
	const CVector3 GetPosition()
	{
		return m_position;
	}

	void SetPosition(const CVector3 pos)
	{
		m_position = pos;
	}
	//店に共通するアップデートの処理を行う関数
	void ShopUpdate();
	//商品の取引を行う関数
	//引数		商品の値段
	//戻り値	取引が成立したかどうか　成立ならtrue不成立ならfalse
	bool Transaction(const int Gold);

protected:
	enum EShopState
	{
		enShopBuy,			//買い物を行うとき
		enShopExecute,		//店を出るとき
		enShopNone,			//何も行っていないとき
		enShopOpen,			//店を開く
		enShopLineup,
		enShopNum,
	};
	struct SLineupPos
	{
		int X = 0;
		int Y = 0;
	};
	CSkinModel			m_skinModel;						//スキンモデル
	CVector3			m_position = CVector3::Zero;		//ポジション
	CVector3			m_scale = CVector3::One;			//スケール
	CQuaternion			m_rotation = CQuaternion::Identity;	//回転
	CSprite				m_backSprite;
	CTexture			m_backTexture;

	CSoundSource		m_shop_bgm;							//店のBGM
	EShopState			m_shopState = enShopNone;			//店の状態
	EShopState			m_selectShop = enShopNone;			//選択中の状態

	static const int	Y_ELEMENT = 3;						//行の要素数
	static const int	X_ELEMENT = 5;						//列の要素数
	SLineupPos			m_lineupSelectPos;					//選んでるアイテムの要素
	CSprite				m_shopLineup[Y_ELEMENT][X_ELEMENT];					//商品のスプライト
	CTexture			m_shopLineuoTexture;								//商品のテクスチャ
	CVector2			m_shopLineupPosition = { -200.0f,200.0f };
	CVector2			m_shopLineupTexSize = { 100.0f,100.0f };
	const CVector2		SHOPLINEUP_POSITION_OFFSET = { 105.0f,105.0f };

	CSprite				m_selectItemSprite;
	CTexture			m_selectItemTexture;
	CVector2			m_slectItemTexPos = { -200.0f,200.0f };
	CVector2			m_selectItemTexSize = { 100.0f,100.0f };

	static const int	SELECT_TEX_ELEMENT = 2;									//セレクト用のスプライトの要素数
	const	CVector2	SELECT_POSITON_START = { 350.0f,-195.0f };				//セレクトテクスチャの初期座標
	CSprite				m_shopSelect[SELECT_TEX_ELEMENT];						//セレクト用のスプライト
	CTexture			m_shopSelectTexture[SELECT_TEX_ELEMENT];				//セレクト用のテクスチャ
	CSprite				m_shopSelectPen;										//ペン用のスプライト
	CTexture			m_shopSelectPenTexture;									//ペン用のテクスチャ
	CVector2			m_shopSelectPosition = {200.0f,-200.0f};
	CVector2			m_shopSelectSize = {200.0f,50.0f};
	CVector2			m_shopSelectPenPosition = { 350.0f,-195.0f };
	CVector2			m_shopSelectPenSize = { 50.0f,50.0f };

	int					m_price[Y_ELEMENT][X_ELEMENT];						//商品の値段を格納している配列

	bool			m_isShoplineupDraw = false;			//ショップ画面を描画するかの判定
	bool			m_isSelectDraw = false;				//セレクト画面を描画するかの判定

	const float			SHOP_DRAW_LENGTH = 3.5f;		//ショップの影響を受ける長さ
};

