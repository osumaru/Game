#include "Message.h"

void CMessage::Init(CVector2 windowSize, wchar_t* textureName)
{
	//ウィンドウの初期化
	CTexture* texture = TextureResource().LoadTexture(L"Assets/sprite/statusWindow.png");
	m_window.Init(texture);
	m_window.SetPosition({ 0.0f,0.0f });
	m_window.SetSize({ 1.0f,1.0f });
	m_window.SetAlpha(0.5f);
	m_windowSize = windowSize;
	//表示するスプライトの初期化
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
	//ウィンドウのサイズを取得
	CVector2 size = m_window.GetSize();
	//ウィンドウのサイズを段々大きくする
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
	//ウィンドウのサイズを設定
	m_window.SetSize(size);
	if (count >= 2)
	{
		//メッセージを描画する
		m_message.SetIsDraw(true);
		//メッセージを段々不透明にしていく
		m_timer += GameTime().GetDeltaFrameTime();
		if (m_timer >= 1.0f)
		{
			m_timer = 1.0f;
			m_isDrawEnd = true;
		}
		//メッセージのアルファ値を設定
		m_message.SetAlpha(m_timer);
	}
}

void CMessage::AfterDraw()
{
	m_window.Draw();
	m_message.Draw();
}
