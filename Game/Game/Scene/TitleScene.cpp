#include "stdafx.h"
#include "TitleScene.h"
#include "SceneManager.h"

CTitleScene::CTitleScene()
{
	//����N������Ȃ������Ƃ�
	if (m_isGameStart)
	{
		m_isGameStart = false;
	}
	else
	{
		//�t�F�[�h�A�E�g�̊J�n
		GetSceneManager().GetFade()->FadeIn();
	}
}

CTitleScene::~CTitleScene()
{

}

bool CTitleScene::Start()
{
	//�t�F�[�h�̎��s���I�������true��Ԃ�
	if (!GetSceneManager().GetFade()->IsExecute())
	{
		return true;
	}
	return false;
}

void CTitleScene::Init()
{
	const CVector2	titlePos = { -1.0f,-1.0f };		//�^�C�g�����W
	const CVector2	titleSize = { 1280.0f,7200.0f };	//�^�C�g���T�C�Y

	m_titleTexture.Load(L"Assets/sprite/TitleBack.png");
	m_title.Init(&m_titleTexture);
	m_title.SetPosition(titlePos);
	m_title.SetSize(titleSize);
	
}

void CTitleScene::Update()
{
	if (Pad().IsTriggerButton(enButtonStart) || GetAsyncKeyState('V'))
	{
		//�Q�[���V�[���֑J��
		GetSceneManager().ChangeScene(GetSceneManager().enGameScene);
		
	}
}

void CTitleScene::AfterDraw()
{
	m_title.Draw();
}
