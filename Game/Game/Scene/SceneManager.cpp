#include "stdafx.h"
#include "SceneManager.h"

void CSceneManager::Init()
{
	m_fade = new CFade;
	Add(m_fade, 15);

	Add(this, 0);
	m_isFadeOut = true;
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
		switch (m_nextSceneState)
		{
			//�^�C�g���V�[���ւ̑J��
		case EnSceneState::enTitleScene:
			//����N��
			if (m_isGameStart)
			{
				m_isGameStart = false;
			}
			else
			{
				//�t�F�[�h�A�E�g�̊J�n
				GetSceneManager().GetFade()->FadeIn();
			}
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
		//���݂̃V�[�����J���p�̃X�e�[�g��
		m_preSceneState = m_nextSceneState;
	}
}

//�V�[���̐؂�ւ��֐�
void CSceneManager::ChangeScene(EnSceneState scene)
{
	//
	if (!m_isFadeOut)
	{
		m_fade->FadeOut();
		m_isFadeOut = true;
	}
	

	//�ύX����V�[�������݂̃V�[���ɂ���
	m_nextSceneState = scene;


}