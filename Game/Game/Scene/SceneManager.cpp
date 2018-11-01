#include "stdafx.h"
#include "SceneManager.h"

//�V�[���̐؂�ւ��֐�
void CSceneManager::ChangeScene(EnSceneState scene)
{

	//�e�V�[���̊J��
	switch (m_sceneState)
	{
		//�^�C�g���V�[���̊J��
	case EnSceneState::enTitleScene:
		Delete(m_titleScene);
		m_titleScene = nullptr;
		break;
		//�Q�[���V�[���̊J��
	case EnSceneState::enGameScene:
		m_gameScene->Release();
		Delete(m_gameScene);
		m_gameScene = nullptr;
		break;
		//���U���g�V�[���̊J��
	case EnSceneState::enResultScene:
		//���U���g�J���̏���������
		break;
		//���[�h�V�[���̊J��
	case EnSceneState::enLoadScene:
		//���[�h�J���̏���������
		break;
	default:
		break;
	}



	//�e�V�[���ւ̑J��
	switch (scene)
	{
		//�^�C�g���V�[���ւ̑J��
	case EnSceneState::enTitleScene:
		m_titleScene = New<CTitleScene>(0);
		m_titleScene->Init();
		break;
		//�Q�[���V�[���ւ̑J��
	case EnSceneState::enGameScene:
		m_gameScene = New<CGameScene>(0);
		m_gameScene->Init();
		break;
		//���U���g�V�[���ւ̑J��
	case EnSceneState::enResultScene:
		break;
		//���U���g�V�[���ւ̑J��
	case EnSceneState::enLoadScene:
		//���[�h�J���̏���������
		break;
	default:
		break;
	}

	//�ύX�����V�[�������݂̃V�[���ɂ���
	m_sceneState = scene;
}