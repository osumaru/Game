#pragma once
#include "INpcState.h"
class CShopNPC : public INpcState
{
public:
	CShopNPC();
	~CShopNPC();
	void Init(const CVector3 position, const CQuaternion rotation);
	void Update();
	void Draw();
	void AfterDraw();
	void Transaction(const int Gold);

private:
	enum EShopState
	{
		enShopBuy,			//買い物を行うとき
		enShopExecute,		//店を出るとき
		enShopNone,			//何も行っていないとき
		enShopLineup,
		enShopNum,
	};
	enum EnShopLineup
	{
		enBluePotion,
		enRedPotion,
		enGreenPotion,
		enYellowPotion, 
		enPotionNum,
	};

	static const int			TEXTURE_NUM = 2;
	static const int			BACK_TEXTURE_NUM = 2;
	CSprite				m_backSprite[2];				//背景のスプライト	
	CTexture			m_backTexture;					//背景のテクスチャ
	CVector2			m_backPosition	= { -480.0f,0.0f };
	CVector2			m_backSize		= { 350.0f,600.0f };
	const  CVector2     BACKTEX_OFFSET_XY{ 380.0f,-200.0f };

	CSprite				m_selectSprite;					//羽ペンのスプライト
	CTexture			m_selectTexture;				//羽ペンのテクスチャ
	CVector2			m_selectTexPosition = { -350.0f,200.0f };
	const CVector2		LINEUP_SELECT_POSITION = { 50.0f,200.0f };
	CVector2			m_lineupSelectTexPosition = LINEUP_SELECT_POSITION;

	CSprite				m_lineupSprite[enPotionNum];	//商品のスプライト
	CTexture			m_lineupTexture[enPotionNum];	//商品のテクスチャ
	CVector2			m_lineupTexPosition = { -140.0f,200.0f };
	CVector2			m_lineupTexSize = { 250.0f,50.0f };
	EnShopLineup		m_lineupState = enBluePotion;
	int					m_lineupPrice[enPotionNum];
	bool				m_drawLineup = false;
	bool				m_isBuy = false;

	CSprite				m_shopSprite[TEXTURE_NUM];
	CTexture			m_shopTexture[TEXTURE_NUM];
	CVector2			m_texturePos = {-500.0f,200.0f};
	CVector2			m_textureSize = {200.0f,50.0f};
	CSoundSource		m_seSound;						//システム音
	bool				m_isTextureDraw = false;		//UIを描画するかの判定
	EShopState			m_shopState = enShopNone;		//ショップの状態
	const float			SHOP_DRAW_LENGTH = 3.5f;		//ショップの影響を受ける長さ
	const int			RECOVERY_MONEY = 20;			//回復アイテムの値段
	
};

