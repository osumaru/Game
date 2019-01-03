#include "stdafx.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "Map/Map.h"
#include "../../Game/Camera/GameCamera.h"
#include "../Player/Player.h"
#include "../UI/MiniMap/MiniMap.h"
#include "../UI/WeaponSelect/WeaponSelect.h"
#include "../UI/PlayerHp/PlayerHp.h"
#include "../UI/Menu/Menu.h"
#include "../UI/Result/Result.h"
#include "../UI/LevelUp/LevelUp.h"
#include "../GameSound/GameSound.h"
#include <thread>

CGameScene::CGameScene()
{
}

CGameScene::~CGameScene()
{
}

void CGameScene::BeforeDead()
{
	//デリートの順番考えてない
	Delete(m_result);
	Delete(m_menu);
	Delete(m_levelUp);
	Delete(m_playerHp);
	Delete(m_weaponSelect);
	GetGameCamera().Destroy();
	Engine().GetEffectEngine().SetCamera(nullptr);
	Delete(m_miniMap);
	Delete(m_map);
	Delete(m_gameSound);

}

bool CGameScene::Start()
{
	//カメラを生成
	GetGameCamera().Create();
	GetGameCamera().Init();
	m_gameSound = New<CGameSound>(0);

	//フェードの実行が終わったらtrueを返す
	if (!GetSceneManager().GetFade()->IsExecute())
	{
		//std::thread ThreadA([&] {
		//マップの初期化
		m_map = New<Map>(0);
		m_map->Init(0);

		//ミニマップの初期化
		m_miniMap = New<CMiniMap>(PRIORITY_UI);
		m_miniMap->Init();


		//UIの初期化
		{
			m_weaponSelect = New<CWeaponSelect>(PRIORITY_UI);
			m_weaponSelect->Init();

			m_playerHp = New<CPlayerHp>(PRIORITY_UI);
			m_playerHp->Init();

			m_levelUp = New<CLevelUp>(PRIORITY_UI);
			m_levelUp->Init();

			m_menu = New<CMenu>(PRIORITY_UI);
			m_menu->Init();

			m_result = New<CResult>(PRIORITY_UI);
			m_result->Init();

		}
		//フェードインの開始
		GetSceneManager().GetFade()->FadeIn();

		//ゲーム開始フラグの設定
		GetSceneManager().SetIsStart(true);
		//});
		//ThreadA.detach();
		return true;

	}
	//return false;

}

void CGameScene::Update()
{
	if (Pad().IsTriggerButton(enButtonRStickPush))
	{
		GetSceneManager().ChangeScene(CSceneManager::enBossScene);
	}
}

