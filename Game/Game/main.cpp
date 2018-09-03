#include "stdafx.h"
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
	Engine().InitD3D(hInst);
	GetGameCamera().Init();
	New<CGameScene>(0)->Init();
	Engine().GameLoop();
	return 0;
}