#pragma once
#include "GameScene.h"


class CSceneManager : public IGameObject
{
public:


	void Init();

	void Update();

	//�Q�[���V�[���̎擾
	CGameScene& GetGameScene()
	{
		return m_gameScene;
	}

	//�V�[���}�l�[�W���[�̃C���X�^���X���擾
	static CSceneManager& GetInstance()
	{
		static CSceneManager sceneManager;
		return sceneManager;
	}

private:


	CGameScene		m_gameScene;	//�Q�[���V�[��

};

static CSceneManager& GetSceneManager()
{

	return CSceneManager::GetInstance();
}
