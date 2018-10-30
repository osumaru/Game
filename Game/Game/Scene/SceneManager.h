#pragma once
#include "GameScene.h"

enum enSeceneState 
{
	enTitleScene,
	enGameScene

};

class CSceneManager : public IGameObject
{
public:
	enum EnSceneState {
		enGameScene,	//�Q�[��
		enResultScene,	//���U���g
		enTitleScene,	//�^�C�g��
	};

	//������
	void Init();

	//�X�V
	void Update();

	//�V�[���ω�
	void ChangeScene(EnSceneState scene);

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

	//���������I���������ݒ�
	void SetEndInit(bool endinit)
	{
		m_isEndInit = endinit;
	}

	//���������I����������擾
	bool GetEndInit()
	{
		return m_isEndInit;
	}

private:


	CGameScene		m_gameScene;			//�Q�[���V�[��
	bool			m_isEndInit = false;	//���������Ă��邩�ǂ���

};

static CSceneManager& GetSceneManager()
{

	return CSceneManager::GetInstance();
}
