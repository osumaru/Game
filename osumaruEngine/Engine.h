#pragma once
#pragma once
#include "GameObject/GameObjectManager.h"
#include "Graphics/Texture.h"
#include "Graphics\RenderTarget.h"
//エンジンクラス

const int FRAME_BUFFER_WIDTH = 1280;
const int FRAME_BUFFER_HEIGHT = 720;

class EffectManager;
class GameObject;
class PhysicsWorld;
class SoundEngine;
class Pad;

class Engine
{
private:
	//コンストラクタ。シングルトンのためプライベートになっている
	Engine();

	//デストラクタ。シングルトンのためプライベートになっている
	~Engine();
public:
	//DirectXを初期化
	void InitD3D(HINSTANCE& hInst);

	//ゲームループ
	void GameLoop();

	//自分のインスタンスを取得
	static Engine& GetEngine()
	{
		static Engine engine;
		return engine;
	}
	//リリース
	void Release()
	{

	}

	//物理ワールドを取得。
	PhysicsWorld& GetPhysicsWorld()
	{
		return *m_physicsWorld;
	}

	//サウンドエンジンを取得
	SoundEngine& GetSoundEngine()
	{
		return *m_soundEngine;
	}

	//パッドの取得
	Pad& GetPad()
	{
		return *m_pad;
	}

	ID3D11Device* GetDevice()
	{
		return m_pD3DDevice;
	}
	
	ID3D11DeviceContext* GetDeviceContext()
	{
		return m_pDeviceContext;
	}

	//インスタンスの生成
	template<class T, class... TArgs>
	T* New(int priority, TArgs... args)
	{
		return m_objectManager.New<T, TArgs...>(priority, args...);
	}

	//インスタンスの削除
	void Delete(GameObject* deleteObject)
	{
		m_objectManager.Delete(deleteObject);
	}

	//インスタンスをオブジェクトマネージャーに登録
	void Add(GameObject* object, int priority)
	{
		m_objectManager.Add(object, priority);
	}


private:

	GameObjectManager						m_objectManager;			//オブジェクトマネージャー
	WNDCLASSEX								m_wc;						//ウィンドウクラス
	ID3D11Device*							m_pD3DDevice;
	int										m_frameBufferWidth;
	int										m_frameBufferHeight;
	IDXGISwapChain*							m_pSwapChain;
	D3D_FEATURE_LEVEL						m_featureLevel;
	ID3D11DeviceContext*					m_pDeviceContext;
	Texture									m_depthStencilTexture;
	RenderTarget							m_backBuffer;
	D3D_DRIVER_TYPE							m_driverType;
	ID3D11RenderTargetView*					m_pBackBuffer;
	HWND									m_hwnd;
	std::unique_ptr<PhysicsWorld>			m_physicsWorld;				//物理ワールド
	std::unique_ptr<SoundEngine>			m_soundEngine;				//サウンドエンジン]
	std::unique_ptr<Pad>					m_pad;
};

//エンジンクラスのインスタンスを取得。
static Engine& GetEngine()
{
	return Engine::GetEngine();
}

//インスタンスの生成
template <class T, class... TArgs>
static T* New(int priority, TArgs... args)
{
	return GetEngine().New<T, TArgs...>(priority, args...);
}
//インスタンスの削除
static void Delete(GameObject* deleteObject)
{
	GetEngine().Delete(deleteObject);
}

static void Add(GameObject* object, int priority)
{
	GetEngine().Add(object, priority);
}

static ID3D11Device* GetDevice()
{
	return GetEngine().GetDevice();
}

static ID3D11DeviceContext* GetDeviceContext()
{
	return GetEngine().GetDeviceContext();
}

//パッドの取得
static Pad& GetPad()
{
	return GetEngine().GetPad();
}

static PhysicsWorld& GetPhysicsWorld()
{
	return GetEngine().GetPhysicsWorld();
}

static SoundEngine& GetSoundEngine()
{
	return GetEngine().GetSoundEngine();
}

