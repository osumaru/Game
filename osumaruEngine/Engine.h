#pragma once
#pragma once
#include "GameObject/GameObjectManager.h"
#include "Graphics/Texture.h"
#include "Graphics\RenderTarget.h"
//エンジンクラス


class CEffectManager;
class CGameObject;
class CPhysicsWorld;
class CSoundEngine;
class CPad;

class CEngine
{
private:
	//コンストラクタ。シングルトンのためプライベートになっている
	CEngine();

	//デストラクタ。シングルトンのためプライベートになっている
	~CEngine();
public:
	//DirectXを初期化
	void InitD3D(HINSTANCE& hInst);

	//ゲームループ
	void GameLoop();

	//自分のインスタンスを取得
	static CEngine& GetEngine()
	{
		static CEngine engine;
		return engine;
	}
	//リリース
	void Release()
	{

	}

	int GetFrameBufferWidth()
	{
		return m_frameBufferWidth;
	}

	int GetFrameBufferHeight()
	{
		return m_frameBufferHeight;
	}

	//物理ワールドを取得。
	CPhysicsWorld& PhysicsWorld()
	{
		return *m_physicsWorld;
	}

	//サウンドエンジンを取得
	CSoundEngine& SoundEngine()
	{
		return *m_soundEngine;
	}

	//パッドの取得
	CPad& Pad()
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
	void Delete(IGameObject* deleteObject)
	{
		m_objectManager.Delete(deleteObject);
	}

	//インスタンスをオブジェクトマネージャーに登録
	void Add(IGameObject* object, int priority)
	{
		m_objectManager.Add(object, priority);
	}


private:

	CGameObjectManager						m_objectManager;			//オブジェクトマネージャー
	WNDCLASSEX								m_wc;						//ウィンドウクラス
	ID3D11Device*							m_pD3DDevice;
	int										m_frameBufferWidth;
	int										m_frameBufferHeight;
	IDXGISwapChain*							m_pSwapChain;
	D3D_FEATURE_LEVEL						m_featureLevel;
	ID3D11DeviceContext*					m_pDeviceContext;
	CTexture									m_depthStencilTexture;
	CRenderTarget							m_backBuffer;
	D3D_DRIVER_TYPE							m_driverType;
	ID3D11RenderTargetView*					m_pBackBuffer;
	HWND									m_hwnd;
	std::unique_ptr<CPhysicsWorld>			m_physicsWorld;				//物理ワールド
	std::unique_ptr<CSoundEngine>			m_soundEngine;				//サウンドエンジン]
	std::unique_ptr<CPad>					m_pad;
};

//エンジンクラスのインスタンスを取得。
static CEngine& Engine()
{
	return CEngine::GetEngine();
}

//インスタンスの生成
template <class T, class... TArgs>
static T* New(int priority, TArgs... args)
{
	return GetEngine().New<T, TArgs...>(priority, args...);
}
//インスタンスの削除
static void Delete(IGameObject* deleteObject)
{
	Engine().Delete(deleteObject);
}

static void Add(IGameObject* object, int priority)
{
	Engine().Add(object, priority);
}

static ID3D11Device* GetDevice()
{
	return Engine().GetDevice();
}

static ID3D11DeviceContext* GetDeviceContext()
{
	return Engine().GetDeviceContext();
}

//パッドの取得
static CPad& Pad()
{
	return Engine().Pad();
}

static CPhysicsWorld& PhysicsWorld()
{
	return Engine().PhysicsWorld();
}

static CSoundEngine& GetSoundEngine()
{
	return Engine().SoundEngine();
}

static int FrameBufferWidth()
{
	return Engine().GetFrameBufferWidth();
}

static int FrameBufferHeight()
{
	return Engine().GetFrameBufferHeight();
}

