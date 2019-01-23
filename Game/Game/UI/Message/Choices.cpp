#include "Choices.h"

void CChoices::Init(wchar_t* select1, wchar_t* select2)
{
	//�I�����̏�����
	m_yes.Init(select1);
	m_yes.SetPosition({ -50.0f, -190.0f});
	m_yes.SetSize({ 0.7f,0.7f });
	m_no.Init(select2);
	m_no.SetPosition({ -50.0f, -290.0f});
	m_no.SetSize({ 0.7f,0.7f });
	//�X�v���C�g�̏�����
	CTexture* texture = TextureResource().LoadTexture(L"Assets/sprite/cursor.png");
	m_cursor.Init(texture);
	m_cursor.SetPosition({ -75.0f, -210.0f });
	m_cursor.SetSize({ 250.0f, 250.0f });
	texture = TextureResource().LoadTexture(L"Assets/sprite/statusWindow.png");
	m_window.Init(texture);
	m_window.SetPosition({ 0.0f, -250.0f });
	m_window.SetSize({ 300.0f, 200.0f });
	m_window.SetAlpha(0.7f);
}

void CChoices::Update()
{
	//�X�e�B�b�N����ɓ|�����A���͏\���L�[�̏��������
	if (Pad().GetLeftStickY() > 0.0f || Pad().IsTriggerButton(enButtonUp))
	{
		//��Ԃ�ύX
		m_state = Yes;
		//�J�[�\���̍��W��ύX
		m_cursor.SetPosition({ -75.0f, -210.0f });
	}
	//�X�e�B�b�N�����ɓ|�����A���͏\���L�[�̉���������
	else if (Pad().GetLeftStickY() < 0.0f || Pad().IsTriggerButton(enButtonDown))
	{
		//��Ԃ�ύX
		m_state = No;
		//�J�[�\���̍��W��ύX
		m_cursor.SetPosition({ -75.0f, -310.0f });
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

void CChoices::PostAfterDraw()
{
	m_window.Draw();
	m_cursor.Draw();
	m_yes.Draw();
	m_no.Draw();
}
