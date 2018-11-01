/*
*	�V�[���}�l�[�W���[�N���X
*/
#pragma once
#include "GameScene.h"
#include "TitleScene.h"
#include "../UI/Fade/Fade.h"

class CSceneManager
{
public:
	enum EnSceneState {
		enTitleScene,	//�^�C�g��
		enGameScene,	//�Q�[��
		enResultScene,	//���U���g
		enLoadScene,	//���[�h
		enSceneNum		//�V�[���̐�
	};

	//������
	void Init();

	//�V�[���ω�
	//scene		�J�ڂ������V�[��
	void ChangeScene(EnSceneState scene);

	//�Q�[���V�[���̎擾
	CGameScene& GetGameScene()
	{
		return *m_gameScene;
	}

	//�V�[���}�l�[�W���[�̃C���X�^���X���擾
	static CSceneManager& GetInstance()
	{
		static CSceneManager sceneManager;
		return sceneManager;
	}
	//�t�F�[�h�̎擾
	CFade* GetFade()
	{
		return m_fade;
	}


private:
	EnSceneState	m_sceneState= enSceneNum;//�V�[���̃X�e�[�g�i���݂̃V�[�������Ă����p�j
	CGameScene*		m_gameScene;			//�Q�[���V�[��
	CTitleScene*	m_titleScene;			//�^�C�g���V�[��
	CFade*			m_fade;					//�t�F�C�h
	//IScene*			m_scene;			//�V�[���̃C���^�[�t�F�[�X
};

//�V�[���}�l�[�W���[�̃C���X�^���X���擾
static CSceneManager& GetSceneManager()
{
	return CSceneManager::GetInstance();
}

//�Q�[���V�[���̎擾
static CGameScene& GetSceneGame()
{
	return GetSceneManager().GetGameScene();
}