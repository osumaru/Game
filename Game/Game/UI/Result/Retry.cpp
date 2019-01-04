#include "Retry.h"

void CRetry::Init()
{
	//�X�v���C�g�̏�����
	CTexture* texture = TextureResource().LoadTexture(L"Assets/sprite/Continue.png");
	m_continue.Init(texture);
	m_continue.SetPosition({ 0.0f, -150.0f});
	m_continue.SetSize({ 250.0f, 250.0f });
	texture = TextureResource().LoadTexture(L"Assets/sprite/Quit.png");
	m_quit.Init(texture);
	m_quit.SetPosition({ 0.0f, -250.0f});
	m_quit.SetSize({ 250.0f, 250.0f });
	texture = TextureResource().LoadTexture(L"Assets/sprite/cursor.png");
	m_cursor.Init(texture);
	m_cursor.SetPosition({ -150.0f, -150.0f });
	m_cursor.SetSize({ 250.0f, 250.0f });
}

void CRetry::Update()
{
	//�X�e�B�b�N����ɓ|�����A���͏\���L�[�̏��������
	if (Pad().GetLeftStickY() > 0.0f || Pad().IsTriggerButton(enButtonUp))
	{
		//��Ԃ�ύX
		m_state = Continue;
		//�J�[�\���̍��W��ύX
		m_cursor.SetPosition({ -150.0f, -150.0f });
	}
	//�X�e�B�b�N�����ɓ|�����A���͏\���L�[�̉���������
	else if (Pad().GetLeftStickY() < 0.0f || Pad().IsTriggerButton(enButtonDown))
	{
		//��Ԃ�ύX
		m_state = Quit;
		//�J�[�\���̍��W��ύX
		m_cursor.SetPosition({ -100.0f, -250.0f });
	}
}

void CRetry::AfterDraw()
{
	m_continue.Draw();
	m_quit.Draw();
	m_cursor.Draw();
}
