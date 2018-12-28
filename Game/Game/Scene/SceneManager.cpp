#include "stdafx.h"
#include "SceneManager.h"

void CSceneManager::Init()
{
	m_fade = New<CFade>(PRIORITY_MAX - 1);
	m_nextSceneState = enTitleScene;
	//SceneManager�N���X��Add
	Add(this, 0);
	m_isFadeOut = true;
}

CSceneManager::~CSceneManager()
{

}

void CSceneManager::BeforeDead()
{
	if (m_fade != nullptr)
	{
		Delete(m_fade);
	}
	if (m_gameScene != nullptr)
	{
		Delete(m_gameScene);
	}
	if (m_titleScene != nullptr)
	{
		Delete(m_titleScene);
	}
	if (m_clearScene != nullptr)
	{
		Delete(m_clearScene);
	}

}

void CSceneManager::Update()
{
	//�t�F�[�h���Ă΂ꂩ���s���I����Ă�����
	if (m_isFadeOut && !m_fade->IsExecute())
	{
		m_isFadeOut = false;

		//�e�V�[���̊J��
		switch (m_preSceneState)
		{
			//�^�C�g���V�[���̊J��
		case EnSceneState::enTitleScene:
			Delete(m_titleScene);
			m_titleScene = nullptr;
			break;
			//�Q�[���V�[���̊J��
		case EnSceneState::enGameScene:
			Delete(m_gameScene);
			m_gameScene = nullptr;
			break;
			//�N���A�V�[���̊J��
		case EnSceneState::enClearScene:
			Delete(m_clearScene);
			m_clearScene = nullptr;
			break;
			//���[�h�V�[���̊J��
		case EnSceneState::enLoadScene:
			//���[�h�J���̏���������
			break;
		default:
			break;
		}

		//�e�V�[���ւ̑J��
		switch (m_nextSceneState)
		{
			//�^�C�g���V�[���ւ̑J��
		case EnSceneState::enTitleScene:
			m_titleScene = New<CTitleScene>(PRIORITY_SCENE);
			break;
			//�Q�[���V�[���ւ̑J��
		case EnSceneState::enGameScene:
			m_gameScene = New<CGameScene>(PRIORITY_SCENE);
			break;
			//�N���A�V�[���ւ̑J��
		case EnSceneState::enClearScene:
			m_clearScene = New<CClearScene>(PRIORITY_SCENE);
			break;
			//���U���g�V�[���ւ̑J��
		case EnSceneState::enLoadScene:
			//���[�h�J���̏���������
			break;
		default:
			break;
		}
		m_isSceneChange = false;
		//���݂̃V�[�����J���p�̃X�e�[�g��
		m_preSceneState = m_nextSceneState;
	}
}

//�V�[���̐؂�ւ��֐�
void CSceneManager::ChangeScene(EnSceneState scene)
{
	//�t�F�[�h�A�E�g���Ă��Ȃ�������
	if (!m_isFadeOut)
	{
		m_fade->FadeOut();
		m_isFadeOut = true;
	}
	
	m_isSceneChange = true;
	//�ύX����V�[�������݂̃V�[���ɂ���
	m_nextSceneState = scene;
}