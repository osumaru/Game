/*
*	�V�[���}�l�[�W���[�N���X
*/
#pragma once
#include "GameScene.h"
#include "TitleScene.h"
#include "ClearScene.h"
#include "../UI/Fade/Fade.h"

class CSceneManager:public IGameObject
{
public:
	enum EnSceneState {
		enTitleScene,	//�^�C�g��
		enGameScene,	//�Q�[��
		enLoadScene,	//���[�h
		enClearScene,	//�N���A
		enSceneNum		//�V�[���̐�
	};
	~CSceneManager();

	//������
	void Init();

	//�X�V
	void Update();

	void BeforeDead()override;

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

	//�t�F�[�h�A�E�g���J�n������
	bool GetFadeOut()
	{
		return m_isFadeOut;
	}

	//�V�[���؂�ւ����s��ꂽ��
	bool GetSceneChange()
	{
		return m_isSceneChange;
	}

private:
	EnSceneState	m_preSceneState= enSceneNum;//�V�[���̃X�e�[�g�i���݂̃V�[�������Ă����p�j
	EnSceneState	m_nextSceneState = enSceneNum;//�V�[���̃X�e�[�g�i���̃V�[�������Ă����p�j
	CGameScene*		m_gameScene=nullptr;			//�Q�[���V�[��
	CTitleScene*	m_titleScene = nullptr;			//�^�C�g���V�[��
	CClearScene*	m_clearScene = nullptr;			//�N���A�V�[��
	CFade*			m_fade;							//�t�F�C�h
	bool			m_isSceneChange = false;		//�V�[���؂�ւ�
	bool			m_isFadeOut = false;		//�t�F�[�h�A�E�g�������ǂ���
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

//�t�F�[�h�̎擾
//static CFade& Fade()
//{
//	return GetSceneManager().GetFade();
//}