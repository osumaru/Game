#include "stdafx.h"
#include "SceneManager.h"



void CSceneManager::Init()
{
	//�Q�[���V�[��
	m_gameScene.Init();
	m_sceneState = enGameScene;

	//�^�C�g���V�[���̏�����
	//m_titleScene.Init();
	//m_sceneState = enTitleScene;
}

void CSceneManager::Update()
{

}

//�V�[���̐؂�ւ��֐�
void CSceneManager::ChangeScene(EnSceneState scene)
{
	//��X�p���Ƃ��|�����[�Ȃ񂿂����g���������ɕς���H

	//�e�V�[���̊J��
	switch (m_sceneState)
	{
		//�^�C�g���V�[���̊J��
	case EnSceneState::enTitleScene:
		//�^�C�g���J���̏���������
		break;
		//�Q�[���V�[���̊J��
	case EnSceneState::enGameScene:
		m_gameScene.Release();
		break;
		//���U���g�V�[���̊J��
	case EnSceneState::enResultScene:
		//���U���g�J���̏���������
		break;
	default:
		break;
	}

	//�e�V�[���ւ̑J��
	switch (scene)
	{
		//�^�C�g���V�[���ւ̑J��
	case EnSceneState::enTitleScene:
		m_titleScene.Init();
		break;
		//�Q�[���V�[���ւ̑J��
	case EnSceneState::enGameScene:
		m_gameScene.Init();
		break;
		//���U���g�V�[���ւ̑J��
	case EnSceneState::enResultScene:
		break;
	default:
		break;
	}
}