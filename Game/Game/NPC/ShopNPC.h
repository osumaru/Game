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
		enShopBuy,			//���������s���Ƃ�
		enShopExecute,		//�X���o��Ƃ�
		enShopNone,			//�����s���Ă��Ȃ��Ƃ�
		enShopNum,
	};
	static const int			TEXTURE_NUM = 2;
	CSprite				m_backSprite;
	CTexture			m_backTexture;
	CSprite				m_selectSprite;					//�H�y���̃X�v���C�g
	CTexture			m_selectTexture;				//�H�y���̃e�N�X�`��
	CVector2			m_selectTexPosition = { -350.0f,200.0f };

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

