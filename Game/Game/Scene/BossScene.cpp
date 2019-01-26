#include "BossScene.h"
#include "SceneManager.h"
#include "Map/Map.h"
#include "../../Game/Camera/GameCamera.h"
#include "../UI/WeaponSelect/WeaponSelect.h"
#include "../UI/PlayerHp/PlayerHp.h"
#include "../UI/Menu/Menu.h"
#include "../UI/Result/Result.h"
#include "../UI/LevelUp/LevelUp.h"
#include "../UI/Message/Message.h"
#include "../UI/Message/Choices.h"
#include "../GameSound/GameSound.h"

void CBossScene::BeforeDead()
{
	Delete(m_result);
	Delete(m_menu);
	Delete(m_levelUp);
	Delete(m_playerHp);
	Delete(m_weaponSelect);
	GetGameCamera().Destroy();
	Engine().GetEffectEngine().SetCamera(nullptr);
	Delete(m_map);
	Delete(m_gameSound);
	Delete(m_choices);
	Delete(m_message);
}

bool CBossScene::Start()
{
	//カメラを生成
	GetGameCamera().Create();
	GetGameCamera().Init();

	m_gameSound = New<CGameSound>(0);

	if (!GetSceneManager().GetFade()->IsExecute())
	{
		//マップの初期化
		m_map = New<Map>(0);
		m_map->Init(1);
		//武器選択のUIを初期化
		m_weaponSelect = New<CWeaponSelect>(PRIORITY_UI);
		m_weaponSelect->Init();
		//プレイヤーHPのUIを初期化
		m_playerHp = New<CPlayerHp>(PRIORITY_UI);
		m_playerHp->Init();
		//レベルアップのUIを初期化
		m_levelUp = New<CLevelUp>(PRIORITY_UI);
		m_levelUp->Init();
		//メニュー画面の初期化
		m_menu = New<CMenu>(PRIORITY_UI);
		m_menu->Init();
		//ゲームオーバーのUIの初期化
		m_result = New<CResult>(PRIORITY_UI);
		m_result->Init();
		//メッセージ表示の初期化
		m_message = New<CMessage>(PRIORITY_UI);
		m_message->Init({ 500.0f,250.0f }, L"Continue");
		m_message->SetIsActive(false);
		//選択肢表示の初期化
		m_choices = New<CChoices>(PRIORITY_UI);
		m_choices->Init(L"はい", L"いいえ");
		m_choices->SetIsActive(false);
	}

	//フェードインの開始
	GetSceneManager().GetFade()->FadeIn();

	return true;
}

void CBossScene::Update()
{
	if (!GetPlayer().GetIsDied())
	{
		//プレイヤーが死んでいなければ何もしない
		return;
	}

	if (m_result->GetDraw()) 
	{
		//コンティニュー表示をアクティブにする
		m_choices->SetIsActive(true);
		m_message->SetIsActive(true);
		//選択肢を選んだらシーン切り替え
		if (m_choices->GetIsSelect())
		{
			//コンティニューを押した
			if (m_choices->GetState() == CChoices::Yes)
			{
				//ボスシーンに遷移
				GetSceneManager().ChangeScene(CSceneManager::enBossScene);
			}
			//やめるを押した
			else
			{
				//ゲームシーンに遷移
				GetSceneManager().ChangeScene(CSceneManager::enGameScene);
			}
		}
	}
}