#include "stdafx.h"
#include "ClearScene.h"
#include "SceneManager.h"

CClearScene::CClearScene()
{
}


CClearScene::~CClearScene()
{
}

bool CClearScene::Start()
{
	//�t�F�[�h�̎��s���I�������true��Ԃ�
	if (!GetSceneManager().GetFade()->IsExecute())
	{
		const CVector2	clearPos = { -1.0f,-1.0f };		//�^�C�g�����W
		const CVector2	clearSize = { 1280.0f,7200.0f };	//�^�C�g���T�C�Y

		m_clearTexture = TextureResource().LoadTexture(L"Assets/sprite/TitleBack.png");
		m_clear.Init(m_clearTexture);
		m_clear.SetPosition(clearPos);
		m_clear.SetSize(clearSize);
		//�t�F�[�h�C���̊J�n
		GetSceneManager().GetFade()->FadeIn();
		return true;
	}
	return false;
}

void CClearScene::Update()
{
	if (Pad().IsTriggerButton(enButtonStart) || GetAsyncKeyState('V'))
	{
		//�Q�[���V�[���֑J��
		GetSceneManager().ChangeScene(GetSceneManager().enTitleScene);

	}
}

void CClearScene::AfterDraw()
{
	m_clear.Draw();
}
