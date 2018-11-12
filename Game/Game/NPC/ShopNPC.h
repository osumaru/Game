#pragma once
#include "INpcState.h"
#include "NpcManager.h"

class CShopNPC:public IGameObject
{
public:
	CShopNPC();
	~CShopNPC();
	void Update();
	void Draw();
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



	static const int			TEXTURE_NUM = 2;
	static const int			BACK_TEXTURE_NUM = 2;
	CSkinModel		m_skinModel;						//�X�L�����f��
	CVector3		m_position = CVector3::Zero;		//�|�W�V����
	CVector3		m_scale = CVector3::One;			//�X�P�[��
	CQuaternion		m_rotation = CQuaternion::Identity;	//��]

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

