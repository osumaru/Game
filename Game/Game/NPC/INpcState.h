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
	//�X�ɋ��ʂ���A�b�v�f�[�g�̏������s���֐�
	void ShopUpdate();
	//���i�̎�����s���֐�
	//����		���i�̒l�i
	//�߂�l	����������������ǂ����@�����Ȃ�true�s�����Ȃ�false
	bool Transaction(const int Gold);

protected:
	enum EShopState
	{
		enShopBuy,			//���������s���Ƃ�
		enShopExecute,		//�X���o��Ƃ�
		enShopNone,			//�����s���Ă��Ȃ��Ƃ�
		enShopOpen,			//�X���J��
		enShopLineup,
		enShopNum,
	};
	struct SLineupPos
	{
		int X = 0;
		int Y = 0;
	};
	CSkinModel			m_skinModel;						//�X�L�����f��
	CVector3			m_position = CVector3::Zero;		//�|�W�V����
	CVector3			m_scale = CVector3::One;			//�X�P�[��
	CQuaternion			m_rotation = CQuaternion::Identity;	//��]
	CSprite				m_backSprite;
	CTexture			m_backTexture;

	CSoundSource		m_shop_bgm;							//�X��BGM
	EShopState			m_shopState = enShopNone;			//�X�̏��
	EShopState			m_selectShop = enShopNone;			//�I�𒆂̏��

	static const int	Y_ELEMENT = 3;						//�s�̗v�f��
	static const int	X_ELEMENT = 5;						//��̗v�f��
	SLineupPos			m_lineupSelectPos;					//�I��ł�A�C�e���̗v�f
	CSprite				m_shopLineup[Y_ELEMENT][X_ELEMENT];					//���i�̃X�v���C�g
	CTexture			m_shopLineuoTexture;								//���i�̃e�N�X�`��
	CVector2			m_shopLineupPosition = { -200.0f,200.0f };
	CVector2			m_shopLineupTexSize = { 100.0f,100.0f };
	const CVector2		SHOPLINEUP_POSITION_OFFSET = { 105.0f,105.0f };

	CSprite				m_selectItemSprite;
	CTexture			m_selectItemTexture;
	CVector2			m_slectItemTexPos = { -200.0f,200.0f };
	CVector2			m_selectItemTexSize = { 100.0f,100.0f };

	static const int	SELECT_TEX_ELEMENT = 2;									//�Z���N�g�p�̃X�v���C�g�̗v�f��
	const	CVector2	SELECT_POSITON_START = { 350.0f,-195.0f };				//�Z���N�g�e�N�X�`���̏������W
	CSprite				m_shopSelect[SELECT_TEX_ELEMENT];						//�Z���N�g�p�̃X�v���C�g
	CTexture			m_shopSelectTexture[SELECT_TEX_ELEMENT];				//�Z���N�g�p�̃e�N�X�`��
	CSprite				m_shopSelectPen;										//�y���p�̃X�v���C�g
	CTexture			m_shopSelectPenTexture;									//�y���p�̃e�N�X�`��
	CVector2			m_shopSelectPosition = {200.0f,-200.0f};
	CVector2			m_shopSelectSize = {200.0f,50.0f};
	CVector2			m_shopSelectPenPosition = { 350.0f,-195.0f };
	CVector2			m_shopSelectPenSize = { 50.0f,50.0f };

	int					m_price[Y_ELEMENT][X_ELEMENT];						//���i�̒l�i���i�[���Ă���z��

	bool			m_isShoplineupDraw = false;			//�V���b�v��ʂ�`�悷�邩�̔���
	bool			m_isSelectDraw = false;				//�Z���N�g��ʂ�`�悷�邩�̔���

	const float			SHOP_DRAW_LENGTH = 3.5f;		//�V���b�v�̉e�����󂯂钷��
};

