#pragma once
class CLevelUp : public IGameObject
{
public:
	CLevelUp();
	~CLevelUp();

	//������
	void Init();

	//�X�V
	void Update();

	//�`��
	void PostAfterDraw();

private:
	CSprite			m_playerLevelUpSprite;							//�v���C���[���x���A�b�v�X�v���C�g
	CTexture*		m_playerLevelUpTexture;							//�v���C���[���x���A�b�v�e�N�X�`��
	const CVector2	m_playerLevelUpPos = {0.0f,10.0f };			//�v���C���[���x���A�b�v���W
	CVector2		m_playerLevelUpSize = { 200.0f,200.0f };			//�v���C���[���x���A�b�v�T�C�Y
	float			m_playerLevelUpAlpha = 0.0f;
	int				m_playerLevelValue = 1;
};

