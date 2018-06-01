#include "stdafx.h"
#include "Test.h"

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
	New<Test>(0)->Init();
	GetEngine().GameLoop();
	return 0;
}