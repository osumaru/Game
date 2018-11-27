#include "stdafx.h"
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
	GetSceneManager().GetInstance().Update();

	Engine().GameLoop();
	Delete(&GetSceneManager());
	Delete(&Sky());
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
#endif // DEBUG
	return 0;
}