#include "stdafx.h"
#include "../../Game/Game/Camera/GameCamera.h"
#include "Player\Player.h"
#include "Scene\GameScene.h"
#include "Scene/SceneManager.h"

using namespace std;
int WINAPI wWinMain(
	HINSTANCE hInst,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow
)
{
	//Direct3D‚ğ‰Šú‰»
	Engine().InitD3D(hInst);
	GetSceneManager().Init();
	Engine().GameLoop();
	return 0;
}