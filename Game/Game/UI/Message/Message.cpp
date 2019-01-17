#include "Message.h"

void CMessage::Init(CVector2 windowSize, wchar_t* textureName)
{
	//�E�B���h�E�̏�����
	CTexture* texture = TextureResource().LoadTexture(L"Assets/sprite/statusWindow.png");
	m_window.Init(texture);
	m_window.SetPosition({ 0.0f,0.0f });
	m_window.SetSize({ 1.0f,1.0f });
	m_window.SetAlpha(0.5f);
	m_windowSize = windowSize;
	//�\������X�v���C�g�̏�����
	wchar_t filePath[256];
	swprintf(filePath, L"Assets/sprite/%s.png", textureName);
	texture = TextureResource().LoadTexture(filePath);
	m_message.Init(texture);
	m_message.SetPosition({ 0.0f,0.0f });
	m_message.SetSize({ 400.0f, 200.0f });
	m_message.SetIsDraw(false);
	m_message.SetAlpha(0.0f);
}

void CMessage::Update()
{
	int count = 0;
	//�E�B���h�E�̃T�C�Y���擾
	CVector2 size = m_window.GetSize();
	//�E�B���h�E�̃T�C�Y��i�X�傫������
	size += m_windowSize * GameTime().GetDeltaFrameTime();
	if (size.x >= m_windowSize.x)
	{
		size.x = m_windowSize.x;
		count++;
	}
	if (size.y >= m_windowSize.y)
	{
		size.y = m_windowSize.y;
		count++;
	}
	//�E�B���h�E�̃T�C�Y��ݒ�
	m_window.SetSize(size);
	if (count >= 2)
	{
		//���b�Z�[�W��`�悷��
		m_message.SetIsDraw(true);
		//���b�Z�[�W��i�X�s�����ɂ��Ă���
		m_timer += GameTime().GetDeltaFrameTime();
		if (m_timer >= 1.0f)
		{
			m_timer = 1.0f;
			m_isDrawEnd = true;
		}
		//���b�Z�[�W�̃A���t�@�l��ݒ�
		m_message.SetAlpha(m_timer);
	}
}

void CMessage::AfterDraw()
{
	m_window.Draw();
	m_message.Draw();
}
