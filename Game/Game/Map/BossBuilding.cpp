#include "BossBuilding.h"
#include "../Camera/GameCamera.h"
#include "../Player/Player.h"
#include "../Scene/SceneManager.h"

void CBossBuilding::Init(CVector3 position)
{
	m_skinModel.Load(L"Assets/modelData/TestBox1.cmo");
	m_position = position;
}

void CBossBuilding::Update()
{
	if (GetSceneManager().GetSceneChange())
	{
		//シーン切り替えしたら消す
		Delete(this);
		return;
	}

	CVector3 playerPos = GetPlayer().GetPosition();
	//プレイヤーとの距離を求める
	CVector3 distance = playerPos - m_position;
	float length = distance.Length();
	if (length < 2.0f)
	{
		//ボスシーンに切り替える
		GetSceneManager().ChangeScene(CSceneManager::enBossScene);
	}

	m_skinModel.Update(m_position, m_rotation, { 1.0f,1.0f,1.0f }, true);
}

void CBossBuilding::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}
