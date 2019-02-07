#include "TitleEnemy.h"
#include "../Camera/GameCamera.h"
#include "../Scene/SceneManager.h"

void CTitleEnemy::Init(const wchar_t* modelName, CVector3 position)
{
	//モデルのロード
	wchar_t filePath[256];
	swprintf(filePath, L"Assets/modelData/%s.cmo", modelName);
	m_skinModel.Load(filePath, &m_animation);
	m_skinModel.SetSpecularPower(0.03f);
	//座標を設定
	m_position = position;
	//アニメーションのロード
	wchar_t animFilePath[256];
	swprintf(animFilePath, L"Assets/modelData/%sStand.tka", modelName);
	wchar_t* animationClip[1];
	animationClip[0] = animFilePath;
	m_animation.Init(animationClip, 1);
	m_animation.SetLoopFlg(0, true);
	m_animation.Play(0);

}

void CTitleEnemy::Update()
{
	if (GetSceneManager().GetSceneChange())
	{
		Delete(this);
		return;
	}
	//アニメーションの更新
	m_animation.Update(GameTime().GetDeltaFrameTime() * 0.6f);
	//モデルの更新
	m_skinModel.Update(m_position, m_rotation, { 1.0f,1.0f,1.0f }, true);
}

void CTitleEnemy::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}
