#include "BossScene.h"
#include "SceneManager.h"
#include "Map/Map.h"
#include "../../Game/Camera/GameCamera.h"
#include "../UI/MiniMap/MiniMap.h"
#include "../UI/WeaponSelect/WeaponSelect.h"
#include "../UI/PlayerHp/PlayerHp.h"
#include "../UI/Menu/Menu.h"
#include "../UI/Result/Result.h"
#include "../UI/LevelUp/LevelUp.h"
#include "../UI/Result/Retry.h"
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
	Delete(m_retry);
}

bool CBossScene::Start()
{
	//�J�����𐶐�
	GetGameCamera().Create();
	GetGameCamera().Init();

	m_gameSound = New<CGameSound>(0);

	if (!GetSceneManager().GetFade()->IsExecute())
	{
		//�}�b�v�̏�����
		m_map = New<Map>(0);
		m_map->Init(1);
		//����I����UI��������
		m_weaponSelect = New<CWeaponSelect>(PRIORITY_UI);
		m_weaponSelect->Init();
		//�v���C���[HP��UI��������
		m_playerHp = New<CPlayerHp>(PRIORITY_UI);
		m_playerHp->Init();
		//���x���A�b�v��UI��������
		m_levelUp = New<CLevelUp>(PRIORITY_UI);
		m_levelUp->Init();
		//���j���[��ʂ̏�����
		m_menu = New<CMenu>(PRIORITY_UI);
		m_menu->Init();
		//�Q�[���I�[�o�[��UI�̏�����
		m_result = New<CResult>(PRIORITY_UI);
		m_result->Init();

		m_retry = New<CRetry>(PRIORITY_UI);
		m_retry->Init();
		m_retry->SetIsActive(false);
	}

	//�t�F�[�h�C���̊J�n
	GetSceneManager().GetFade()->FadeIn();

	return true;
}

void CBossScene::Update()
{
	if (!GetPlayer().GetIsDied())
	{
		//�v���C���[������ł��Ȃ���Ή������Ȃ�
		return;
	}
	//�R���e�B�j���[�\�����A�N�e�B�u�ɂ���
	m_retry->SetIsActive(true);
	//A�{�^������������V�[���؂�ւ�
	if (Pad().IsTriggerButton(enButtonA))
	{
		//�R���e�B�j���[��������
		if (m_retry->GetState() == CRetry::Continue)
		{
			//�{�X�V�[���ɑJ��
			GetSceneManager().ChangeScene(CSceneManager::enBossScene);
		}
		//��߂��������
		else 
		{
			//�Q�[���V�[���ɑJ��
			GetSceneManager().ChangeScene(CSceneManager::enGameScene);
		}
	}
}