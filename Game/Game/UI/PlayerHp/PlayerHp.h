#pragma once

class PlayerHp : public IGameObject
{
public:
	//������
	void Init();

	//�X�V
	void Update();

	//�`��
	void Draw();
private:
	CSprite m_playerHpSprite;		//�v���C���[��HP�X�v���C�g
	CTexture m_playerHpTexture;		//�v���C���[��HP�e�N�X�`��
	const CVector2 m_playerHpPos = {-400.0f,300.0f};	//�v���C���[��HP���W
	const CVector2 m_playerHpSize = {450.0f,100.0f};	//�v���C���[��HP�T�C�Y
};

