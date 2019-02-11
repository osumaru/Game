#include "Message.h"

void CMessage::Init(CVector2 windowSize, wchar_t* textureName)
{
	//�E�B���h�E�̏�����
	CTexture* texture = TextureResource().LoadTexture(L"Assets/sprite/MessageWindow.png");
	m_window.Init(texture);
	m_window.SetPosition({ 0.0f,0.0f });
	m_window.SetSize(windowSize);
	m_window.SetAlpha(0.0f);
	//�\������X�v���C�g�̏�����
	wchar_t filePath[256];
	swprintf(filePath, L"Assets/sprite/%s.png", textureName);
	texture = TextureResource().LoadTexture(filePath);
	m_message.Init(texture);
	m_message.SetPosition({ 0.0f,0.0f });
	const float messageSizeRate = 0.7f;
	CVector2 messageSize = windowSize * messageSizeRate;
	m_message.SetSize(messageSize);
	m_message.SetAlpha(0.0f);
}

void CMessage::Update()
{
	bool isDrawEnd = false;
	//���b�Z�[�W��i�X�s�����ɂ��Ă���
	m_timer += GameTime().GetDeltaFrameTime() * m_alphaSpeed;
	if (m_timer >= 1.0f)
	{
		m_timer = 1.0f;
		isDrawEnd = true;
	}
	//�A���t�@�l��ݒ�
	m_window.SetAlpha(m_timer);
	m_message.SetAlpha(m_timer);

	if (isDrawEnd && Pad().IsTriggerButton(enButtonA))
	{
		Delete(this);
	}
}

void CMessage::PostAfterDraw()
{
	m_window.Draw();
	m_message.Draw();
}
