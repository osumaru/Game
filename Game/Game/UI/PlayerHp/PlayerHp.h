#pragma once

class PlayerHp : public GameObject
{
public:
	//������
	void Init();

	//�X�V
	void Update();

	//�`��
	void Draw();
private:
	Sprite m_playerHpSprite;		//�v���C���[��HP�X�v���C�g
	Texture m_playerHpTexture;		//�v���C���[��HP�e�N�X�`��
	const Vector2 m_playerHpPos = {-400.0f,300.0f};	//�v���C���[��HP���W
	const Vector2 m_playerHpSize = {450.0f,100.0f};	//�v���C���[��HP�T�C�Y
};

