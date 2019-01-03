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
	//�f���[�g�̏��ԍl���ĂȂ�
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
	//�J�����𐶐�
	GetGameCamera().Create();
	GetGameCamera().Init();
	m_gameSound = New<CGameSound>(0);

	//�t�F�[�h�̎��s���I�������true��Ԃ�
	if (!GetSceneManager().GetFade()->IsExecute())
	{
		//std::thread ThreadA([&] {
		//�}�b�v�̏�����
		m_map = New<Map>(0);
		m_map->Init(0);

		//�~�j�}�b�v�̏�����
		m_miniMap = New<CMiniMap>(PRIORITY_UI);
		m_miniMap->Init();


		//UI�̏�����
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
		//�t�F�[�h�C���̊J�n
		GetSceneManager().GetFade()->FadeIn();

		//�Q�[���J�n�t���O�̐ݒ�
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

