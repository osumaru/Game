#include "BossBuilding.h"
#include "../Camera/GameCamera.h"
#include "../Player/Player.h"
#include "../Scene/SceneManager.h"
#include "../UI/Message/Message.h"
#include "../UI/Message/Choices.h"

void CBossBuilding::Init(CVector3 position,CQuaternion rotation)
{
	//モデルの初期化
	m_skinModel.Load(L"Assets/modelData/CastleDoor3.cmo");
	//座標を設定
	m_position = position;
	m_rotation = rotation;
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
		//選択中でないならタイマーを進める
		m_timer += GameTime().GetDeltaFrameTime();
	}
	//プレイヤーの座標を取得
	CVector3 playerPos = GetPlayer().GetPosition();
	//プレイヤーとの距離を求める
	CVector3 distance = playerPos - m_position;
	float length = distance.Length();
	if (!m_isChoice && length < 2.0f && m_timer >= 3.0f)
	{
		//メッセージと選択肢を表示する
		m_message = New<CMessage>(PRIORITY_UI);
		m_message->Init({ 500.0f,250.0f }, L"bossTry");
		m_choices = New<CChoices>(PRIORITY_UI);
		m_choices->Init();
		m_isChoice = true;
		m_timer = 0.0f;
	}

	if (m_isChoice)
	{
		//選択中ならプレイヤーは動かない
		GetPlayer().SetIsAction(false);
		//選択肢を選んだ
		if (m_choices->GetIsSelect())
		{
			//はいを選んだ
			if (m_choices->GetState() == CChoices::Yes)
			{
				//ボスシーンに切り替える
				GetSceneManager().ChangeScene(CSceneManager::enBossScene);
				m_isChoice = false;
			}
			//いいえを選んだ
			else
			{
				//プレイヤーを動かせるようにする
				GetPlayer().SetIsAction(true);
				m_isChoice = false;
			}
			m_choices->SetDeleteFlag(true);
		}
	}

	m_skinModel.Update(m_position, m_rotation, { 1.0f,1.0f,1.0f });
}

void CBossBuilding::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}
