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

private:
	CSprite m_aButton;			//A�{�^��
	CSprite m_pickUp;			//�E��
	CSprite	m_back;				//�w�i
	int		m_drawCount = 0;	//�`�悷�邩�����߂�J�E���g�B0�Ȃ�`�悵�Ȃ�
};