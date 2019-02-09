#include "Message.h"

void CMessage::Init(CVector2 windowSize, wchar_t* textureName)
{
	//�E�B���h�E�̏�����
	CTexture* texture = TextureResource().LoadTexture(L"Assets/sprite/MessageWindow.png");
	m_window.Init(texture);
	m_window.SetPosition({ 0.0f,0.0f });
	m_window.SetSize({ 600.0f, 150.0f });
	m_window.SetAlpha(0.0f);
	m_windowSize = windowSize;
	//�\������X�v���C�g�̏�����
	wchar_t filePath[256];
	swprintf(filePath, L"Assets/sprite/%s.png", textureName);
	texture = TextureResource().LoadTexture(filePath);
	m_message.Init(texture);
	m_message.SetPosition({ 0.0f,0.0f });
	m_message.SetSize({ 300.0f, 100.0f });
	m_message.SetAlpha(0.0f);
}

void CMessage::Update()
{
	//���b�Z�[�W��i�X�s�����ɂ��Ă���
	m_timer += GameTime().GetDeltaFrameTime() * m_alphaSpeed;
	if (m_timer >= 1.0f)
	{
		m_timer = 1.0f;
		m_isDrawEnd = true;
	}
	//�A���t�@�l��ݒ�
	m_window.SetAlpha(m_timer);
	m_message.SetAlpha(m_timer);

	if (m_isDrawEnd && Pad().IsTriggerButton(enButtonA))
	{
		Delete(this);
	}
}

void CMessage::PostAfterDraw()
{
	m_window.Draw();
	m_message.Draw();
}
