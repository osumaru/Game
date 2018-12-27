#pragma once
#include "../Item/IItem.h"
class IShop	:	public IGameObject
{
public:
	IShop();
	virtual ~IShop();
	virtual void Init(const CVector3 position, const CQuaternion rotation) = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	//バイナリーデータの読み込み
	void LoadFile(const wchar_t* filePath);
	//バイナリーデータの追加
	void AddFile(const wchar_t* filePath);
	
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

	//ショップの状態を取得
	const int GetShopState()
	{
		return m_shopState;
	}

	//商品の取引を行う関数
	//引数		商品の値段
	//戻り値	取引が成立したかどうか　成立ならtrue不成立ならfalse
	bool Transaction(const int Gold);

protected:
	enum EShopState
	{
		enShopNone,			//何も行っていないとき
		enShopBuy,			//買い物を行うとき
		enShopExecute,		//店を出るとき
		enShopOpen,			//店を開く
		enShopLineup,
		enShopNum,
	};
	struct ShopItem
	{
		IItem::SItemStatus	ItemStatus;				//アイテムの情報
		CSprite			ItemSprite;				//アイテムのスプライト
		CTexture*			ItemTexture;			//アイテムのテクスチャ
	};

	CSkinModel			m_skinModel;						//スキンモデル
	CAnimation			m_animation;
	CVector3			m_position = CVector3::Zero;		//ポジション
	CVector3			m_scale = CVector3::One;			//スケール
	CQuaternion			m_rotation = CQuaternion::Identity;	//回転
	CSprite				m_backSprite;
	CTexture*			m_backTexture;
	EShopState			m_shopState = enShopNone;			//店の状態
	EShopState			m_selectShop = enShopNone;			//選択中の状態

	static const int	ITEM_ELEMENT = 5;										//行の要素数
	int					m_lineupSelectNumber = 0;							//選んでるアイテムの要素
	ShopItem			m_items[ITEM_ELEMENT];									//商品の情報
	CVector2			m_shopLineupPosition = { -220.0f,200.0f };
	CVector2			m_shopLineupTexSize = { 80.0f,80.0f };
	const CVector2		SHOPLINEUP_POSITION_OFFSET = { 80.0f,85.0f };

	CSprite				m_selectItemSprite;
	CTexture*			m_selectItemTexture;
	CVector2			m_slectItemTexPos = { -220.0f,200.0f };
	CVector2			m_selectItemTexSize = { 80.0f,80.0f };

	static const int	SELECT_TEX_ELEMENT = 2;									//セレクト用のスプライトの要素数
	const	CVector2	SELECT_POSITON_START = { 350.0f,-195.0f };				//セレクトテクスチャの初期座標
	CSprite				m_shopSelect[SELECT_TEX_ELEMENT];						//セレクト用のスプライト
	CTexture*			m_shopSelectTexture[SELECT_TEX_ELEMENT];				//セレクト用のテクスチャ
	CSprite				m_shopSelectPen;										//ペン用のスプライト
	CTexture*			m_shopSelectPenTexture;									//ペン用のテクスチャ
	CVector2			m_shopSelectPosition = {200.0f,-200.0f};
	CVector2			m_shopSelectSize = {200.0f,50.0f};
	CVector2			m_shopSelectPenPosition = { 350.0f,-195.0f };
	CVector2			m_shopSelectPenSize = { 50.0f,50.0f };

	bool					m_isShoplineupDraw = false;							//ショップ画面を描画するかの判定
	bool					m_isSelectDraw = false;								//セレクト画面を描画するかの判定
	const float				SHOP_DRAW_LENGTH = 3.5f;							//ショップの影響を受ける長さ
	wchar_t					m_filePath[256];
	bool					m_isTransaction = false;							//取引を行うかの判定
	CFont					m_itemNameFont[ITEM_ELEMENT];
	CFont					m_itemPriceFont[ITEM_ELEMENT];
	CVector2				m_fontPosition{ -340.0f,215.0f };
	CVector2				FONT_POSITION_OFFSET = { 190.0f,85.0f };
	
	
};

