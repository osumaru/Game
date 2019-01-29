#pragma once
class CBossHp : public IGameObject
{
public:
	//������
	void Init();

	//�X�V
	void Update();

	//�`��
	void PostAfterDraw();

private:
	CSprite			m_bossHpSprite;							//�{�X��HP�X�v���C�g
	CTexture*		m_bossHpTexture;						//�{�X��HP�e�N�X�`��
	const CVector2	m_bossHpPos = { -400.0f,-250.0f };		//�{�X��HP���W
	CVector2		m_bossHpSize = { 300.0f,100.0f };		//�{�X��HP�T�C�Y
	const CVector2	m_bossHpCenterPos = { 0.0f,0.0f };		//�{�X��HP��_���W
	float			m_hpSubtractSpeed = 1.0f;				//�{�X��HP���������鑬�x

	CSprite			m_bossHpBackSprite;						//�{�X��HP�o�b�N�O���E���h�X�v���C�g
	CTexture*		m_bossHpBackTexture;					//�{�X��HP�o�b�N�O���E���h�e�N�X�`��
	const CVector2	m_bossHpBackPos = { -400.0f,-250.0f };	//�{�X��HP�o�b�N�O���E���h���W
	CVector2		m_bossHpBackSize = { 300.0f,100.0f };	//�{�X��HP�o�b�N�O���E���h�T�C�Y
	const CVector2	m_bossHpBackCenterPos = { 0.0f,0.0f };	//�{�X��HP�o�b�N�O���E���h��_���W

	CSprite			m_bossHpFrameSprite;						//�{�X��HP�o�b�N�O���E���h�X�v���C�g
	CTexture*		m_bossHpFrameTexture;					//�{�X��HP�o�b�N�O���E���h�e�N�X�`��
	const CVector2	m_bossHpFramePos = { -415.0f,-235.0f };	//�{�X��HP�o�b�N�O���E���h���W
	CVector2		m_bossHpFrameSize = { 380.0f,130.0f };	//�{�X��HP�o�b�N�O���E���h�T�C�Y
	const CVector2	m_bossHpFrameCenterPos = { 0.0f,0.0f };	//�{�X��HP�o�b�N�O���E���h��_���W

	int				m_bossHp = 0;							//�{�X��HP�̒l
	//int				m_bossHpSizeUp = 3;						//�{�X��HP�̑傫���𒲐�����p�̕ϐ�
	float			m_bossMaxHp = 0;						//�{�X�̍ő�Hp
	float			m_bossMaxHpSizeX = 1000.0f;				//�{�X�̍ő�X�����̑傫��
};

