#include "stdafx.h"
#include "Scene/SceneManager.h"
#include <time.h>
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
	Light().SetAmbientLight({ 0.5f,0.5f,0.5f,0.5f });
	Light().SetDiffuseLight(0, { 0.5f,0.5f,0.5f,1.0f });
	Light().SetDiffuseLightDir(0, { 0.0f, -1.0f, 1.0f, 1.0f });
	//�������t�F�[�h�Ȃǂ�
	GetSceneManager().Init();
	GetSceneManager().GetInstance().Update();
	Random().Init((unsigned int)time(NULL));
	Engine().GetTBDR().SetIsActive(false);
	Engine().GameLoop();
	Delete(&GetSceneManager());
	Delete(&Sky());
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
#endif // DEBUG
	return 0;
}