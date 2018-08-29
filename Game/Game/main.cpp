#include "stdafx.h"
#include "Test.h"
#include "GameCamera.h"
#include "Player\Player.h"
#include "Map\Map.h"
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
	New<Map>(0)->Init(0);
	New<GameScene>(0)->Init();
	GetEngine().GameLoop();
	return 0;
}