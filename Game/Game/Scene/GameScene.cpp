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
#include "../UI/GetItem/GetItem.h"
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

}

bool CGameScene::Start()
{
	//カメラを生成
	GetGameCamera().Create();
	GetGameCamera().Init();
	GetGameCamera().SetIsActiveUpdate(true);
	

	Light().SetAmbientLight({ 0.0f, 0.0f, 0.0f, 1.0f });
	Sky().SetLight(Light());
	Light().SetAmbientLight({ 0.0f, 0.0f, 0.0f, 0.3f });
	const float diffuseLight[DIFFUSE_LIGHT_NUM] = { 0.4f, 0.1f, 0.1f, 0.1f };
	CVector4 diffuseDir[DIFFUSE_LIGHT_NUM] =
	{
		{1.0f, -1.0f, 2.0f, 0.0f},
		{1.0f, 0.0f, 1.0f, 0.0f},
		{0.0f, -1.0f, 0.0f, 0.0f},
		{-10.0f, 1.0f, 3.0f, 0.0f}
	};

	for (int i = 0; i < DIFFUSE_LIGHT_NUM; i++)
	{
		Light().SetDiffuseLight(i, { diffuseLight[i], diffuseLight[i], diffuseLight[i], 1.0f });
		Light().SetDiffuseLightDir(i, diffuseDir[i]);
	}
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

			m_getItem = New<CGetItem>(PRIORITY_UI);
			m_getItem->Init();
		}
		//フェードインの開始
		GetSceneManager().GetFade()->FadeIn();

		//ゲーム開始フラグの設定
		GetSceneManager().SetIsStart(true);
		//});
		//ThreadA.detach();
		GetSceneManager().GetGameSound()->SetGameSound(CGameSound::enWorldBgm);
		return true;

	}
	//return false;

}

void CGameScene::Update()
{
	if (GetPlayer().GetIsDied())
	{
		GetSceneManager().ChangeScene(CSceneManager::enGameScene);
	}
}

