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
	void Init();

	//�X�V
	void Update() override;

	//�`��
	void PostAfterDraw() override;

	void SetIteName(CTexture* texture, wchar_t* itemName);
private:
	CSprite	m_sprite[2];
	CFont	m_font;
	float	m_drawTime = 0.0f;
	bool	m_isDraw = false;
};