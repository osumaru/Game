#include "stdafx.h"
//#include "../../Game/Game/Camera/GameCamera.h"
//#include "Player\Player.h"
//#include "Scene\GameScene.h"
#include "Scene/SceneManager.h"

using namespace std;
int WINAPI wWinMain(
	HINSTANCE hInst,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow
)
{
	//Direct3D��������
	Engine().InitD3D(hInst);
	//�������t�F�[�h�Ȃǂ�
	GetSceneManager().Init();
	//�t�F�[�h�C���̊J�n
	//GetSceneManager().GetFade()->FadeIn();
	//�Q�[���V�[���֑J��
	GetSceneManager().ChangeScene(GetSceneManager().enGameScene);
	GetSceneManager().GetInstance().Update();

	Engine().GameLoop();
	return 0;
}