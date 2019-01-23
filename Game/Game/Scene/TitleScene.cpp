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
	//カメラを生成
	GetGameCamera().Create();
	GetGameCamera().Init();
	GetGameCamera().SetIsActiveUpdate(false);

	//ゲーム音楽の初期化
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
	//フェードの実行が終わったらtrueを返す
	if (!GetSceneManager().GetFade()->IsExecute())
	{
		//マップの初期化
		m_map = New<Map>(0);
		m_map->Init(2);

		//スプライトの初期化
		CTexture* texture = TextureResource().LoadTexture(L"Assets/sprite/title.png");
		m_title.Init(texture);
		m_title.SetPosition({ 0.0f, 250.0f });
		m_title.SetSize({ 700.0f, 300.0f });
		texture = TextureResource().LoadTexture(L"Assets/sprite/start.png");
		m_start.Init(texture);
		m_start.SetPosition({0.0f, -180.0f});
		m_start.SetSize({ 500.0f, 300.0f });

		//フェードインの開始
		GetSceneManager().GetFade()->FadeIn();
		return true;
	}

	return false;
}

void CTitleScene::Update()
{
	//タイマーに毎フレームの時間を加算
	m_timer += GameTime().GetDeltaFrameTime();
	//スプライトの透明度を計算する
	if (!m_isNoColor) 
	{
		//カラーがある
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
		//カラーがない
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
		//フェードの実行中は返す
		if (GetSceneManager().GetFade()->IsExecute())
		{
			return;
		}
		const float StartVolume = 0.3f;
		CSoundSource* StartSound = New<CSoundSource>(0);
		StartSound->Init("Assets/sound/SystemSound/StartSE.wav");
		StartSound->Play(false);
		StartSound->SetVolume(StartVolume);
		//ゲームシーンへ遷移
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
