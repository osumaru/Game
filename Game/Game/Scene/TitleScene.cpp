#include "stdafx.h"
#include "TitleScene.h"
#include "SceneManager.h"

CTitleScene::CTitleScene()
{

}

CTitleScene::~CTitleScene()
{

}

bool CTitleScene::Start()
{
	//�t�F�[�h�̎��s���I�������true��Ԃ�
	if (!GetSceneManager().GetFade()->IsExecute())
	{
		const CVector2	titlePos = { -1.0f,-1.0f };		//�^�C�g�����W
		const CVector2	titleSize = { 1280.0f,7200.0f };	//�^�C�g���T�C�Y

		m_titleTexture.Load(L"Assets/sprite/TitleBack.png");
		m_title.Init(&m_titleTexture);
		m_title.SetPosition(titlePos);
		m_title.SetSize(titleSize);
		//�t�F�[�h�C���̊J�n
		GetSceneManager().GetFade()->FadeIn();
		return true;
	}
	return false;
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
