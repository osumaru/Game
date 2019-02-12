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
#include "../UI/AllowRemain/ArrowRemain.h"


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
	//Delete(m_gameSound);
	Delete(m_arrowRemain);
}

bool CBossScene::Start()
{
	//カメラを生成
	GetGameCamera().Create();
	GetGameCamera().Init();

	//m_gameSound = New<CGameSound>(0);

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
		m_message = nullptr;
		m_choices = nullptr;

		m_arrowRemain = New<CArrowRemain>(PRIORITY_UI);
		m_arrowRemain->Init();

		GetSceneManager().GetGameSound()->SetGameSound(CGameSound::EnSoundState::enBossBgm);
		//フェードインの開始
		GetSceneManager().GetFade()->FadeIn();
	}
	
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
		if (m_message == nullptr)
		{
			//メッセージ表示の初期化
			m_message = New<CMessage>(PRIORITY_UI);
			m_message->Init({ 480.0f,150.0f }, L"Continue");
		}
		if (m_choices == nullptr)
		{
			//選択肢表示の初期化
			m_choices = New<CChoices>(PRIORITY_UI);
			m_choices->Init();
		}

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
			m_isChoice = false;
		}
	}
}