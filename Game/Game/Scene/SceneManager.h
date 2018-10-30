/*
*	�V�[���}�l�[�W���[�N���X
*/
#pragma once
#include "GameScene.h"
#include "TitleScene.h"

class CSceneManager:public IGameObject
{
public:
	enum EnSceneState {
		enTitleScene,	//�^�C�g��
		enGameScene,	//�Q�[��
		enResultScene,	//���U���g
		enSceneNum		//�V�[���̐�
	};

	//������
	void Init();

	//�X�V
	void Update();

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


private:
	EnSceneState	m_sceneState= enSceneNum;//�V�[���̃X�e�[�g�i���݂̃V�[�������Ă����p�j
	CGameScene*		m_gameScene;			//�Q�[���V�[��
	CTitleScene*	m_titleScene;			//�^�C�g���V�[��
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