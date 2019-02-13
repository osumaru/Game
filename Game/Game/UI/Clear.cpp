#include "Clear.h"
#include "../Scene/SceneManager.h"

void CClear::Init()
{
	m_sprite.Init(TextureResource().LoadTexture(L"Assets/sprite/clear.png"));
	m_sprite.SetPosition({0.0f, 0.0f});
	m_sprite.SetSize({750.0f, 250.0f});

}

void CClear::Update()
{
	const float ALPHA_LIMIT = 3.0f;
	if(m_alpha < ALPHA_LIMIT)
	{
		m_alpha += GameTime().GetDeltaFrameTime();
		m_sprite.SetAlpha(m_alpha / ALPHA_LIMIT);
	}
	else
	{
		GetSceneManager().ChangeScene(CSceneManager::enTitleScene);
		Delete(this);
	}
}

void CClear::PostAfterDraw()
{
	m_sprite.Draw();
}