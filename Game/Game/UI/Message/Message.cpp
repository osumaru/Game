#include "Message.h"
#include "../../Scene/SceneManager.h"
#include "../../Map/Map.h"

void CMessage::Init(CVector2 windowSize, wchar_t* textureName)
{
	//ウィンドウの初期化
	CTexture* texture = TextureResource().LoadTexture(L"Assets/sprite/MessageWindow.png");
	m_window.Init(texture);
	m_window.SetPosition({ 0.0f,0.0f });
	m_window.SetSize(windowSize);
	m_window.SetAlpha(0.0f);
	//メッセージの初期化
	wchar_t filePath[256];
	swprintf(filePath, L"Assets/sprite/%s.png", textureName);
	texture = TextureResource().LoadTexture(filePath);
	m_message.Init(texture);
	m_message.SetPosition({ 0.0f,0.0f });
	const float messageSizeRate = 0.7f;
	CVector2 messageSize = windowSize * messageSizeRate;
	m_message.SetSize(messageSize);
	m_message.SetAlpha(0.0f);
	//背景の初期化
	texture = TextureResource().LoadTexture(L"Assets/sprite/Black.png");
	m_background.Init(texture);
	m_background.SetPosition({ 0.0f,0.0f });
	m_background.SetSize({ 1280.0f, 720.0f });
	m_background.SetAlpha(0.0f);
	//他のオブジェクトの更新を止める
	GetSceneManager().GetMap()->SetIsMapChipActiveUpdate(false);
}

void CMessage::Update()
{
	bool isDrawEnd = false;
	//メッセージを段々不透明にしていく
	m_timer += GameTime().GetDeltaFrameTime() * m_alphaSpeed;
	if (m_timer >= 1.0f)
	{
		m_timer = 1.0f;
		isDrawEnd = true;
	}
	//アルファ値を設定
	m_background.SetAlpha(m_timer / 2.0f);
	m_window.SetAlpha(m_timer);
	m_message.SetAlpha(m_timer);

	if (isDrawEnd && Pad().IsTriggerButton(enButtonA))
	{
		//決定音を鳴らす
		CSoundSource* desideSound = New<CSoundSource>(0);
		desideSound->Init("Assets/sound/SystemSound/EquipOn.wav");
		desideSound->Play(false);
		//他のオブジェクトの更新を戻す
		GetSceneManager().GetMap()->SetIsMapChipActiveUpdate(true);
		Delete(this);
	}
}

void CMessage::PostAfterDraw()
{
	m_background.Draw();
	m_window.Draw();
	m_message.Draw();
}
