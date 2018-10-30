#include "stdafx.h"
#include "SceneManager.h"



void CSceneManager::Init()
{

	m_gameScene.Init();

}

void CSceneManager::Update()
{

}

void CSceneManager::ChangeScene(EnSceneState scene)
{
	//�Q�[���V�[��������������Ă�����
	if (m_isEndInit)
	{
		m_gameScene.Release();
	}
	//m_gameScene.Release();
	switch (scene)
	{
	//�^�C�g���V�[���ւ̑J��
	case EnSceneState::enTitleScene:
		break;
	//�Q�[���V�[���ւ̑J��
	case EnSceneState::enGameScene:
		m_gameScene.Init();
		break;
	//���U���g�V�[���ւ̑J��
	case EnSceneState::enResultScene:
		break;
	}
}