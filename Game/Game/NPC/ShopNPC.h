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
		enShopBuy,			//���������s���Ƃ�
		enShopExecute,		//�X���o��Ƃ�
		enShopNone,			//�����s���Ă��Ȃ��Ƃ�
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
	CSprite				m_backSprite[2];				//�w�i�̃X�v���C�g	
	CTexture			m_backTexture;					//�w�i�̃e�N�X�`��
	CVector2			m_backPosition	= { -480.0f,0.0f };
	CVector2			m_backSize		= { 350.0f,600.0f };
	const  CVector2     BACKTEX_OFFSET_XY{ 380.0f,-200.0f };

	CSprite				m_selectSprite;					//�H�y���̃X�v���C�g
	CTexture			m_selectTexture;				//�H�y���̃e�N�X�`��
	CVector2			m_selectTexPosition = { -350.0f,200.0f };
	const CVector2		LINEUP_SELECT_POSITION = { 50.0f,200.0f };
	CVector2			m_lineupSelectTexPosition = LINEUP_SELECT_POSITION;

	CSprite				m_lineupSprite[enPotionNum];	//���i�̃X�v���C�g
	CTexture			m_lineupTexture[enPotionNum];	//���i�̃e�N�X�`��
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
	CSoundSource		m_seSound;						//�V�X�e����
	bool				m_isTextureDraw = false;		//UI��`�悷�邩�̔���
	EShopState			m_shopState = enShopNone;		//�V���b�v�̏��
	const float			SHOP_DRAW_LENGTH = 3.5f;		//�V���b�v�̉e�����󂯂钷��
	const int			RECOVERY_MONEY = 20;			//�񕜃A�C�e���̒l�i
	
};

