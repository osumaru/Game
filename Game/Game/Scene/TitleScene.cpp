#include "stdafx.h"
#include "TitleScene.h"
#include "SceneManager.h"
#include "Map/Map.h"
#include "../Camera/GameCamera.h"
#include "../GameSound/GameSound.h"

CTitleScene::CTitleScene()
{

}

CTitleScene::~CTitleScene()
{

}

bool CTitleScene::Start()
{
	//�J�����𐶐�
	GetGameCamera().Create();
	GetGameCamera().Init();
	GetGameCamera().SetIsActiveUpdate(false);

	//�Q�[�����y�̏�����
	m_gameSound = New<CGameSound>(0);

	Light().SetAmbientLight({ 0.0f, 0.0f, 0.0f, 0.1f });
	Sky().SetLight(Light());
	Light().SetAmbientLight({ 0.0f, 0.0f, 0.0f, 0.0f });
	const float diffuseLight[DIFFUSE_LIGHT_NUM] = { 0.05f, 0.05f, 0.0f, 0.0f };
	CVector4 diffuseDir[DIFFUSE_LIGHT_NUM] =
	{
		{1.0f, -1.0f, 0.0f, 0.0f},
		{1.0f, 0.0f, 1.0f, 0.0f},
		{0.0f, 0.0f, 1.0f, 0.0f},
		{0.0f, -1.0f, 0.0f, 0.0f}
	};
	
	for (int i = 0; i < DIFFUSE_LIGHT_NUM; i++)
	{
		Light().SetDiffuseLight(i, {diffuseLight[i], diffuseLight[i], diffuseLight[i], 1.0f});
		Light().SetDiffuseLightDir(i, diffuseDir[i]);
	}
	//�t�F�[�h�̎��s���I�������true��Ԃ�
	if (!GetSceneManager().GetFade()->IsExecute())
	{
		//�}�b�v�̏�����
		m_map = New<Map>(0);
		m_map->Init(2);

		//�X�v���C�g�̏�����
		CTexture* texture = TextureResource().LoadTexture(L"Assets/sprite/title.png");
		m_title.Init(texture);
		m_title.SetPosition({ 0.0f, 250.0f });
		m_title.SetSize({ 700.0f, 300.0f });
		texture = TextureResource().LoadTexture(L"Assets/sprite/start.png");
		m_start.Init(texture);
		m_start.SetPosition({0.0f, -180.0f});
		m_start.SetSize({ 500.0f, 300.0f });

		//�t�F�[�h�C���̊J�n
		GetSceneManager().GetFade()->FadeIn();
		return true;
	}

	return false;
}

void CTitleScene::Update()
{
	//�^�C�}�[�ɖ��t���[���̎��Ԃ����Z
	m_timer += GameTime().GetDeltaFrameTime();
	//�X�v���C�g�̓����x���v�Z����
	if (!m_isNoColor) 
	{
		//�J���[������
		if (m_timer < ALPHA_TIME)
		{
			float t = m_timer / ALPHA_TIME;
			m_start.SetAlpha(max(1.0f - t, 0.0f));
		}
		else 
		{
			m_start.SetAlpha(0.0f);
			m_isNoColor = true;
			m_timer = 0.0f;
		}
	}
	else 
	{
		//�J���[���Ȃ�
		if (m_timer < ALPHA_TIME)
		{
			float t = m_timer / ALPHA_TIME;
			m_start.SetAlpha(min(t, 1.0f));
		}
		else 
		{
			m_start.SetAlpha(1.0f);
			m_isNoColor = false;
			m_timer = 0.0f;
		}
	}

	if (Pad().IsTriggerButton(enButtonStart) || GetAsyncKeyState('V'))
	{
		//�t�F�[�h�̎��s���͕Ԃ�
		if (GetSceneManager().GetFade()->IsExecute())
		{
			return;
		}
		const float StartVolume = 0.3f;
		CSoundSource* StartSound = New<CSoundSource>(0);
		StartSound->Init("Assets/sound/SystemSound/StartSE.wav");
		StartSound->Play(false);
		StartSound->SetVolume(StartVolume);
		//�Q�[���V�[���֑J��
		GetSceneManager().ChangeScene(GetSceneManager().enGameScene);
		
	}
}

void CTitleScene::AfterDraw()
{
	EnAlphaBlendState backupState = Engine().GetCurrentAlphaBlendState();
	Engine().SetAlphaBlendState(enAlphaBlendStateTranslucent);
	m_title.Draw();
	m_start.Draw();
	Engine().SetAlphaBlendState(backupState);
}

void CTitleScene::BeforeDead()
{
	Delete(m_map);
	Delete(m_gameSound);
}
