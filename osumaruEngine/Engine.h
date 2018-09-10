#pragma once
#pragma once
#include "GameObject/GameObjectManager.h"
#include "Graphics/Texture.h"
#include "Graphics\RenderTarget.h"
#include "Resource/TextureResource.h"
#include "Resource/SkinmodelResource.h"
#include "Resource/ShaderResource.h"
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

	//フレームバッファの横幅を取得
	int GetFrameBufferWidth()
	{
		return m_frameBufferWidth;
	}

	//フレームバッファの縦幅を取得
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

	CSkinmodelResource& SkinmodelResource()
	{
		return m_skinmodelResource;
	}

	CTextureResource& TextureResource()
	{
		return m_textureResource;
	}

	CShaderResource& ShaderResource()
	{
		return m_shaderResource;
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
	CTexture								m_depthStencilTexture;
	CRenderTarget							m_backBuffer;
	D3D_DRIVER_TYPE							m_driverType;
	ID3D11RenderTargetView*					m_pBackBuffer;
	ID3D11DepthStencilView*					m_depthStencil;
	HWND									m_hwnd;
	std::unique_ptr<CPhysicsWorld>			m_physicsWorld;				//物理ワールド
	std::unique_ptr<CSoundEngine>			m_soundEngine;				//サウンドエンジン]
	std::unique_ptr<CPad>					m_pad;
	CTextureResource						m_textureResource;
	CSkinmodelResource						m_skinmodelResource;
	CShaderResource							m_shaderResource;
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
	return Engine().New<T, TArgs...>(priority, args...);
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

static CSoundEngine& SoundEngine()
{
	return Engine().SoundEngine();
}

static CTextureResource& TextureResource()
{
	return Engine().TextureResource();
}

static CSkinmodelResource& SkinmodelResource()
{
	return Engine().SkinmodelResource();
}

static CShaderResource& ShaderResource()
{
	return Engine().ShaderResource();
}

static int FrameBufferWidth()
{
	return Engine().GetFrameBufferWidth();
}

static int FrameBufferHeight()
{
	return Engine().GetFrameBufferHeight();
}

