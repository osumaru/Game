#include "engineStdafx.h"
#include "Engine.h"
#include "Physics\Physics.h"
#include "Timer\GameTime.h"
#include "Timer/StopWatch.h"
#include "Sound\SoundEngine.h"
#include "Input\Pad.h"
#include "Sky.h"

int MakeHash(const wchar_t* str)
{
	int hash = 0;
	int len = (int)wcslen(str);
	for (int i = 0; i < len; i++)
	{
		hash = hash * 37 + str[i];
	}
	return hash;
}

int MakeHash(const char* str)
{
	int hash = 0;
	int len = (int)strlen(str);
	for (int i = 0; i < len; i++)
	{
		hash = hash * 37 + str[i];
	}
	return hash;
}


LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

CEngine::CEngine() :
	m_objectManager(),
	m_wc(),
	m_pD3DDevice(nullptr),
	m_frameBufferWidth(1280),
	m_frameBufferHeight(720)
{
	
}

CEngine::~CEngine()
{
	//インスタンスの消せてないやつがいるので適当に複数回インスタンス削除をする(複数回するのは親のデストラクタで子の解放関数を読んでいる事があるから
	for(int i = 0;i < 5;i++)
	{
		m_objectManager->DeleteExecute();
	}

	delete m_objectManager;
	delete m_physicsWorld;
	delete m_soundEngine;
}

void CEngine::InitD3D(HINSTANCE& hInst)
{

	UNREFERENCED_PARAMETER(hInst);
	//ウィンドウクラスを作成
	m_wc =
	{
		sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc,0L,0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		"Game", NULL
	};
	//ウィンドウクラスを登録
	RegisterClassEx(&m_wc);

	//ウィンドウを作成
	m_hwnd = CreateWindow("Game", "Game",
		WS_OVERLAPPEDWINDOW, 0, 0, m_frameBufferWidth, m_frameBufferHeight,
		NULL, NULL, m_wc.hInstance, NULL);

	m_objectManager = new CGameObjectManager;
	m_objectManager->Init();
	// show the window
	ShowWindow(m_hwnd, SW_SHOWDEFAULT);
	UpdateWindow(m_hwnd);

	UINT createDeviceFlags = 0;
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = sizeof(featureLevels) / sizeof(featureLevels[0]);
	DXGI_SWAP_CHAIN_DESC sd;
	memset(&sd, 0, sizeof(sd));
	sd.BufferCount = 1;									//スワップチェインのバッファ数。通常は1
	sd.BufferDesc.Width = m_frameBufferWidth;			//フレームバッファの幅	
	sd.BufferDesc.Height = m_frameBufferHeight;			//フレームバッファの高さ
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;	//フレームバッファのフォーマット
	sd.BufferDesc.RefreshRate.Numerator = 60;			//モニタのリフレッシュレート。(バックバッファとフロントバッファを入れ替えるタイミングとなる。)
	sd.BufferDesc.RefreshRate.Denominator = 1;			
	sd.OutputWindow = m_hwnd;							//フレームバッファを出力するウィンドウ
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.Windowed = TRUE;	
	sd.SampleDesc.Count	= 1;							//ピクセル単位のマルチサンプリングの数。MSAAはなし
	sd.SampleDesc.Quality = 0;							//MSAAなし。
	//すべてのドライバタイプでスワップチェインの作成を試す。
	HRESULT hr = E_FAIL;
	for (auto driverType : driverTypes)
	{
		hr = D3D11CreateDeviceAndSwapChain(NULL, driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &sd, &m_pSwapChain, &m_pD3DDevice, &m_featureLevel, &m_pDeviceContext);
		if (SUCCEEDED(hr))
		{
			//スワップチェインを作成できたのでループを抜ける。
			break;
		}
	}
	ID3D11Texture2D * p_RT;
	hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)(&p_RT));

	// ビューポート設定
	m_viewPortState.Init();
	m_viewPortState.SetViewPort(m_pDeviceContext, enViewPortGame);
	m_physicsWorld = new CPhysicsWorld;
	m_physicsWorld->Init();
	m_soundEngine = new CSoundEngine;
	m_soundEngine->Init();
	m_pad = std::make_unique<CPad>();
	for (int i = 0; i < MAIN_RENDER_TARGET_NUM; i++)
	{
		m_mainRenderTarget[i].CreateRenderTarget(m_frameBufferWidth, m_frameBufferHeight, DXGI_FORMAT_R32G32B32A32_FLOAT);
		m_mainRenderTarget[i].CreateDepthStencilBuffer(m_frameBufferWidth, m_frameBufferHeight);
	}
	m_alphaBlend.Init(m_pD3DDevice);
	m_depthState.Init(m_pD3DDevice);
	m_rasterizerState.Init(m_pD3DDevice);
	m_alphaBlend.SetBlendState(m_pDeviceContext, enAlphaBlendStateNone);
	m_rasterizerState.SetRasterizerState(m_pDeviceContext, enRasterizerState3D);
	m_depthState.SetDepthStencilState(m_pDeviceContext, enDepthStencilState3D);
	m_deferred.Init();
	m_postEffect.Init(m_pSwapChain);
	m_shadowMap.Init(100.0f);
	m_pointLightManager.Init();
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(m_pDeviceContext.Get());
	m_effectEngine.Init();
	GameTime().Init();
	m_tbdr.Init();
	Sky().Init(nullptr);
}

void CEngine::SetCamera(const CCamera* camera)
{
	m_tbdr.SetCamera(camera);
	m_deferred.SetCamera(camera);
	m_physicsWorld->SetCamera(camera);
	m_effectEngine.SetCamera(camera);
	Sky().SetCamera(camera);
	m_shadowMap.SetGameCamera(camera);
}
void CEngine::GameLoop()
{
	//ゲームループ
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			CStopWatch sw;
			sw.Start();
			if (GetAsyncKeyState(VK_RSHIFT))
			{
				m_shaderResource.ReLoad();
			}
			m_objectManager->Execute(m_deferred, m_postEffect);
			m_pSwapChain->Present(0, 0);
			m_physicsWorld->Update();
			m_soundEngine->Update();
			m_effectEngine.Update();
			m_pad->Update();
			sw.Stop();
			GameTime().Update(sw);
		}
	}

	UnregisterClass("shader Tutorial", m_wc.hInstance);
}