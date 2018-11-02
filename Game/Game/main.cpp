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
	//Direct3Dを初期化
	Engine().InitD3D(hInst);
	//初期化フェードなどの
	GetSceneManager().Init();
	//フェードインの開始
	//GetSceneManager().GetFade()->FadeIn();
	//ゲームシーンへ遷移
	GetSceneManager().ChangeScene(GetSceneManager().enGameScene);
	GetSceneManager().GetInstance().Update();

	Engine().GameLoop();
	return 0;
}