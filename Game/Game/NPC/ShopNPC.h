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

private:
	enum EShopState
	{
		enShopBuy,			//買い物を行うとき
		enShopExecute,		//店を出るとき
		enShopNone,			//何も行っていないとき
		enShopNum,
	};
	static const int			TEXTURE_NUM = 2;
	CSprite				m_backSprite;
	CTexture			m_backTexture;
	CSprite				m_selectSprite;					//羽ペンのスプライト
	CTexture			m_selectTexture;				//羽ペンのテクスチャ
	CVector2			m_selectTexPosition = { -350.0f,200.0f };

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

