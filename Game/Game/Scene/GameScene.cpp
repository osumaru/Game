#include "stdafx.h"
#include "../Scene/GameScene.h"
#include "Map/Map.h"
#include "../Player/Player.h"
#include "../UI/MiniMap/MiniMap.h"
#include "../UI/WeaponSelect/WeaponSelect.h"
#include "../UI/PlayerHp/PlayerHp.h"
#include "../UI/Menu/Menu.h"
#include "../UI/Result/Result.h"
#include "../UI/LevelUp/LevelUp.h"
#include "../../Game/Camera/GameCamera.h"
#include "SceneManager.h"

CGameScene::CGameScene()
{
	//フェードアウトの開始
	GetSceneManager().GetFade()->FadeIn();
}

CGameScene::~CGameScene()
{
}

void CGameScene::Release()
{
	//デリートの順番考えてない
	Delete(m_result);
	Delete(m_menu);
	Delete(m_levelUp);
	Delete(m_playerHp);
	Delete(m_weaponSelect);
	GetGameCamera().Destroy();
	Delete(m_miniMap);
	Delete(m_map);

}

bool CGameScene::Start()
{
	//フェードの実行が終わったらtrueを返す
	if (!GetSceneManager().GetFade()->IsExecute())
	{
		return true;
	}
	return false;
}

void CGameScene::Init()
{
	//マップの初期化
	m_map = New<Map>(0);
	m_map->Init(0);

	//ミニマップの初期化
	m_miniMap = New<CMiniMap>(0);
	m_miniMap->Init();

	//カメラを生成
	GetGameCamera().Create();
	GetGameCamera().Init();
	/*if (!GetGameCamera().IsStart())
	{
		GetGameCamera().Start();
	}*/
	//UIの初期化
	{
		m_weaponSelect = New<CWeaponSelect>(0);
		m_weaponSelect->Init();

		m_playerHp = New<CPlayerHp>(0);
		m_playerHp->Init();

		m_levelUp = New<CLevelUp>(0);
		m_levelUp->Init();

		m_menu = New<CMenu>(0);
		m_menu->Init();

		m_result = New<CResult>(0);
		m_result->Init();
	}
}

void CGameScene::Update()
{
}

