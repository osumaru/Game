#include "BossBuilding.h"
#include "../Camera/GameCamera.h"
#include "../Player/Player.h"
#include "../Scene/SceneManager.h"
#include "../UI/Message/Message.h"
#include "../UI/Message/Choices.h"

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

	if (!m_isChoice)
	{
		m_timer += GameTime().GetDeltaFrameTime();
	}

	CVector3 playerPos = GetPlayer().GetPosition();
	//プレイヤーとの距離を求める
	CVector3 distance = playerPos - m_position;
	float length = distance.Length();
	if (!m_isChoice && length < 2.0f && m_timer >= 3.0f)
	{
		m_message = New<CMessage>(PRIORITY_UI);
		m_message->Init({ 500.0f,250.0f }, L"bossTry");
		m_choices = New<CChoices>(PRIORITY_UI);
		m_choices->Init(L"はい", L"いいえ");
		m_isChoice = true;
		m_timer = 0.0f;
	}

	if (m_isChoice)
	{
		GetPlayer().SetIsAction(false);
		if (m_choices->GetIsSelect())
		{
			if (m_choices->GetState() == CChoices::Yes)
			{
				//ボスシーンに切り替える
				GetSceneManager().ChangeScene(CSceneManager::enBossScene);
			}
			else
			{
				GetPlayer().SetIsAction(true);
				m_isChoice = false;
			}
			Delete(m_message);
			Delete(m_choices);
		}
	}

	m_skinModel.Update(m_position, m_rotation, { 1.0f,1.0f,1.0f }, true);
}

void CBossBuilding::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}
