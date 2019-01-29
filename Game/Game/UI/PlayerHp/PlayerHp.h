#pragma once

class CPlayerHp : public IGameObject
{
public:
	//������
	void Init();

	//�X�V
	void Update();

	//�`��
	void PostAfterDraw();

private:
	CSprite			m_playerHpSprite;							//�v���C���[��HP�X�v���C�g
	CTexture*		m_playerHpTexture;							//�v���C���[��HP�e�N�X�`��
	const CVector2	m_playerHpPos = {-620.0f,270.0f};			//�v���C���[��HP���W
	CVector2		m_playerHpSize = {300.0f,40.0f};			//�v���C���[��HP�T�C�Y
	const CVector2	m_playerHpCenterPos = { 0.0f,1.0f };		//�v���C���[��HP��_���W
	float			m_hpSubtractSpeed = 1.0f;					//�v���C���[��HP���������鑬�x

	CSprite			m_playerHpBackSprite;						//�v���C���[��HP�o�b�N�O���E���h�X�v���C�g
	CTexture*		m_playerHpBackTexture;						//�v���C���[��HP�o�b�N�O���E���h�e�N�X�`��
	const CVector2	m_playerHpBackPos = { -620.0f,270.0f };		//�v���C���[��HP�o�b�N�O���E���h���W
	CVector2		m_playerHpBackSize = { 300.0f,40.0f };		//�v���C���[��HP�o�b�N�O���E���h�T�C�Y
	const CVector2	m_playerHpBackCenterPos = { 0.0f,1.0f };	//�v���C���[��HP�o�b�N�O���E���h��_���W

	CSprite			m_playerHpFrameSprite;						//�v���C���[��HP�o�b�N�O���E���h�X�v���C�g
	CTexture*		m_playerHpFrameTexture;						//�v���C���[��HP�o�b�N�O���E���h�e�N�X�`��
	const CVector2	m_playerHpFramePos = { -624.0f,268.0f };		//�v���C���[��HP�o�b�N�O���E���h���W
	CVector2		m_playerHpFrameSize = { 300.0f,44.0f };		//�v���C���[��HP�o�b�N�O���E���h�T�C�Y
	const CVector2	m_playerHpFrameCenterPos = { 0.0f,1.0f };	//�v���C���[��HP�o�b�N�O���E���h��_���W

	int				m_playerHp=100;								//�v���C���[��HP�̒l
	float			m_playerMaxHp = 100;						//�v���C���[�̍ő�Hp
	float			m_playerMaxHpSizeX = 400.0f;				//�v���C���[�̍ő�X�����̑傫��
	float			m_delayTime = 0.0f;							//�o�b�N��HP������n�߂�܂ł̒x������
};

