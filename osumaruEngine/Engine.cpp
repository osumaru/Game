#include "engineStdafx.h"
#include "Engine.h"
#include "Physics\Physics.h"
#include "Timer\GameTime.h"
#include "Timer/StopWatch.h"
#include "Sound\SoundEngine.h"
#include "Input\Pad.h"

LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		Engine().Release();
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int MakeHash(const char* string)
{
	int hash = 0;
	int len = (int)strlen(string);
	for (int i = 0; i < len; i++)
	{
		hash = hash * 37 + string[i];
	}
	return hash;
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
	Release();
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


	m_objectManager.Init();
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
	m_depthStencilTexture.Create(m_frameBufferWidth, m_frameBufferHeight, CTexture::enDepthStencil, DXGI_FORMAT_D24_UNORM_S8_UINT);

	m_backBuffer.Create(p_RT, (ID3D11Texture2D*)m_depthStencilTexture.GetTexture(), m_frameBufferWidth, m_frameBufferHeight, true);
	m_pBackBuffer = m_backBuffer.GetRenderTarget();
	ID3D11DepthStencilView* depthStencil = m_backBuffer.GetDepthStencil();
	m_pDeviceContext->OMSetRenderTargets(1, &m_pBackBuffer, depthStencil);

	ID3D11DepthStencilState* depthStencilState;
	D3D11_DEPTH_STENCIL_DESC depthDesc;
	ZeroMemory(&depthDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));

	depthDesc.DepthFunc = D3D11_COMPARISON_LESS;
	depthDesc.DepthEnable = true;
	//depthDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	//depthDesc.StencilEnable = true;
	m_pD3DDevice->CreateDepthStencilState(&depthDesc, &depthStencilState);
	m_pDeviceContext->OMSetDepthStencilState(depthStencilState, 0);
	D3D11_RASTERIZER_DESC rasterizerDesc;
	ID3D11RasterizerState* rasterizerState;
	ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_FRONT;
	m_pD3DDevice->CreateRasterizerState(&rasterizerDesc, &rasterizerState);
	m_pDeviceContext->RSSetState(rasterizerState);
	
	// ビューポート設定
	D3D11_VIEWPORT vp;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width = 1280;
	vp.Height = 720;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	m_pDeviceContext->RSSetViewports(1, &vp);
	m_physicsWorld = std::make_unique<CPhysicsWorld>();
	m_physicsWorld->Init();
	m_soundEngine = std::make_unique<CSoundEngine>();
	m_soundEngine->Init();
	m_pad = std::make_unique<CPad>();
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
			float color[4] = { 0.0f, 0.0f, 1.0f, 0.0f };
			m_pDeviceContext->ClearRenderTargetView(m_pBackBuffer, color);
			m_pDeviceContext->ClearDepthStencilView(m_backBuffer.GetDepthStencil(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
			m_objectManager.Execute();
			m_physicsWorld->Update();
			m_soundEngine->Update();
			m_pad->Update();
			m_pSwapChain->Present(0, 0);
			sw.Stop();

			float limitTime = 1.0f / 60.0f;
			if (sw.GetElapsedTime() < limitTime)
			{
				DWORD sleepTime = max(0.0, limitTime * 1000.0 - (DWORD)sw.GetElapsedTimeMill());
				Sleep(sleepTime);
				GameTime().SetFrameDeltaTime(limitTime);
			}
			else
			{
				GameTime().SetFrameDeltaTime((float)sw.GetElapsedTime());
			}
		}
	}

	UnregisterClass("shader Tutorial", m_wc.hInstance);
}