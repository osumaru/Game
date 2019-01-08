#include "Choices.h"

void CChoices::Init(wchar_t* select1, wchar_t* select2)
{
	//�I�����̏�����
	m_yes.Init(select1);
	m_yes.SetPosition({ 0.0f, -150.0f});
	m_yes.SetSize({ 250.0f, 250.0f });
	m_no.Init(select2);
	m_no.SetPosition({ 0.0f, -250.0f});
	m_no.SetSize({ 250.0f, 250.0f });
	//�X�v���C�g�̏�����
	CTexture* texture = TextureResource().LoadTexture(L"Assets/sprite/cursor.png");
	m_cursor.Init(texture);
	m_cursor.SetPosition({ -150.0f, -150.0f });
	m_cursor.SetSize({ 250.0f, 250.0f });
}

void CChoices::Update()
{
	//�X�e�B�b�N����ɓ|�����A���͏\���L�[�̏��������
	if (Pad().GetLeftStickY() > 0.0f || Pad().IsTriggerButton(enButtonUp))
	{
		//��Ԃ�ύX
		m_state = Yes;
		//�J�[�\���̍��W��ύX
		m_cursor.SetPosition({ -150.0f, -150.0f });
	}
	//�X�e�B�b�N�����ɓ|�����A���͏\���L�[�̉���������
	else if (Pad().GetLeftStickY() < 0.0f || Pad().IsTriggerButton(enButtonDown))
	{
		//��Ԃ�ύX
		m_state = No;
		//�J�[�\���̍��W��ύX
		m_cursor.SetPosition({ -100.0f, -250.0f });
	}
}

void CChoices::AfterDraw()
{
	m_yes.Draw();
	m_no.Draw();
	m_cursor.Draw();
}
