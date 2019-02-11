/*
*	�A�C�e�����E��UI�N���X
*/

#pragma once

class CGetItem : public IGameObject
{
public:
	//������
	void Init();

	//�X�V
	void Update() override;

	//�`��
	void PostAfterDraw() override;

	//�`��J�E���g�𑝂₷
	void AddDrawCount()
	{
		m_drawCount++;
	}

	//�`��J�E���g�����炷
	void SubtractDrawCount()
	{
		m_drawCount--;
	}
	void ItemeNameDraw(CTexture* texture,wchar_t* ItemName )
	{
		m_isDrawItemName = true;
		m_sprite[1].Init(texture);
		m_sprite[1].SetSize({ 80,80.0f });
		m_sprite[1].SetPosition({ -200.0f,-250.0f });
		m_font.SetString(ItemName);
	}
	void NoItemeNameDraw()
	{
		m_isDrawItemName = false;
	}

private:
	CSprite m_aButton;			//A�{�^��
	CSprite m_pickUp;			//�E��
	CSprite	m_back;				//�w�i
	int		m_drawCount = 0;	//�`�悷�邩�����߂�J�E���g�B0�Ȃ�`�悵�Ȃ�
	CSprite								m_sprite[2];
	CFont								m_font;
	bool								m_isDrawItemName = false;
};