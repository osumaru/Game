#include "stdafx.h"
#include "Test.h"
#include "GameCamera.h"
#include "Player\Player.h"
#include "Scene\GameScene.h"

using namespace std;
int WINAPI wWinMain(
	HINSTANCE hInst,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow
)
{
	//Direct3D‚ğ‰Šú‰»
	GetEngine().InitD3D(hInst);
	GetGameCamera().Init();
	New<GameScene>(0)->Init();
	GetEngine().GameLoop();
	return 0;
}