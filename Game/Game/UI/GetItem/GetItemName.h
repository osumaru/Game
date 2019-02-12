/*
*	�l�������A�C�e����\������N���X
*/

#pragma once

class CGetItemName : public IGameObject
{
public:
	//������
	//texture	�e�N�X�`��
	//itemName	�A�C�e���̖��O
	void Init(CTexture* texture, wchar_t* itemName);

	//�X�V
	void Update() override;

	//�`��
	void PostAfterDraw() override;

private:
	CSprite	m_sprite[2];
	CFont	m_font;
	float	m_drawTime = 0.0f;
};