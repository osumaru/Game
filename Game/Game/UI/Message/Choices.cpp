#include "Choices.h"

void CChoices::Init()
{
	//�X�v���C�g�̏�����
	CTexture* texture = TextureResource().LoadTexture(L"Assets/sprite/yes.png");
	m_yes.Init(texture);
	m_yes.SetPosition({ -75.0f, -150.0f });
	m_yes.SetSize({ 160.0f, 50.0f });
	m_yes.SetAlpha(0.0f);
	texture = TextureResource().LoadTexture(L"Assets/sprite/no.png");
	m_no.Init(texture);
	m_no.SetPosition({ 75.0f, -150.0f });
	m_no.SetSize({ 160.0f, 50.0f });
	m_no.SetAlpha(0.0f);
	texture = TextureResource().LoadTexture(L"Assets/sprite/cursor.png");
	m_cursor.Init(texture);
	m_cursor.SetPosition(m_no.GetPosition());
	m_cursor.SetSize({ 125.0f, 50.0f });
	m_cursor.SetAlpha(0.0f);
	texture = TextureResource().LoadTexture(L"Assets/sprite/MessageWindow.png");
	m_window.Init(texture);
	m_window.SetPosition({ 0.0f, -150.0f });
	m_window.SetSize({ 500.0f, 100.0f });
	m_window.SetAlpha(0.0f);
}

void CChoices::Update()
{
	//�����ɂȂ��Ă���
	if (m_isAlpha) 
	{
		m_timer += GameTime().GetDeltaFrameTime();
		if (m_timer >= 1.0f)
		{
			//�s�����ɂȂ���
			m_timer = 1.0f;
			m_isAlpha = false;
		}
		m_yes.SetAlpha(m_timer);
		m_no.SetAlpha(m_timer);
		m_cursor.SetAlpha(m_timer);
		m_window.SetAlpha(m_timer);
	}
	else 
	{
		//�X�e�B�b�N���E�ɓ|�����A���͏\���L�[�̉E��������
		if (Pad().GetLeftStickX() > 0.0f || Pad().IsTriggerButton(enButtonRight))
		{
			//��Ԃ�ύX
			m_state = No;
			//�J�[�\���̍��W��ύX
			m_cursor.SetPosition(m_no.GetPosition());
		}
		//�X�e�B�b�N�����ɓ|�����A���͏\���L�[�̍���������
		else if (Pad().GetLeftStickX() < 0.0f || Pad().IsTriggerButton(enButtonLeft))
		{
			//��Ԃ�ύX
			m_state = Yes;
			//�J�[�\���̍��W��ύX
			m_cursor.SetPosition(m_yes.GetPosition());
		}

		if (Pad().IsTriggerButton(enButtonA))
		{
			//�I��
			m_isSelect = true;
		}
		else
		{
			m_isSelect = false;
		}
	}
}

void CChoices::PostAfterDraw()
{
	m_window.Draw();
	m_yes.Draw();
	m_no.Draw();
	m_cursor.Draw();
}
