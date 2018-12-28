#pragma once
#pragma once
#include "GameObject/GameObjectManager.h"
#include "Graphics/Texture.h"
#include "Graphics\RenderTarget.h"
#include "Resource/TextureResource.h"
#include "Resource/SkinmodelResource.h"
#include "Resource/ShaderResource.h"
#include "Resource/AnimationResource.h"
#include "Graphics/Primitive.h"
#include "Graphics/Light.h"
#include "Graphics/ConstantBuffer.h"
#include "Graphics/PostRendering/Deferred.h"
#include "Graphics/State/AlphaBlendState.h"
#include "Graphics/State/DepthStencilState.h"
#include "Graphics/State/RasterizerState.h"
#include "Graphics/PreRendering/ShadowMap.h"
#include "Graphics/State/ViewPortState.h"
#include "Graphics/PointLightManager.h"
#include "Effect/EffectEngine.h"
#include "Resource/EffectResource.h"

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
	//頂点レイアウト
	struct SVSLayout
	{
		CVector4 position;
		CVector2	uv;
	};

	//DirectXを初期化
	void InitD3D(HINSTANCE& hInst);

	//ゲームループ
	void GameLoop();

	//自分のインスタンスを取得
	static CEngine& GetEngine()
	{
		static CEngine instance;
		return instance;
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
		return m_pD3DDevice.Get();
	}
	
	ID3D11DeviceContext* GetDeviceContext()
	{
		return m_pDeviceContext.Get();
	}

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& GetShaderResource(EnRenderTarget numRenderTarget)
	{
		return  m_deferred.GetShaderResource(numRenderTarget);
	}

	//インスタンスの生成
	template<class T, class... TArgs>
	T* New(int priority, TArgs... args)
	{
		return m_objectManager->New<T, TArgs...>(priority, args...);
	}

	//インスタンスの削除
	void Delete(IGameObject* deleteObject)
	{
		m_objectManager->Delete(deleteObject);
	}

	//インスタンスをオブジェクトマネージャーに登録
	void Add(IGameObject* object, int priority)
	{
		m_objectManager->Add(object, priority);
	}
	CLight& Light()
	{
		return m_light;
	}

	CRenderTarget& GetMainRenderTarget()
	{
		return m_mainRenderTarget[m_currentRenderTargetNum];
	}

	void SwitchingRenderTarget()
	{
		m_currentRenderTargetNum ^= 1;
	}

	//すべてのオブジェクトをアクティブ化
	void AllActive()
	{
		m_objectManager->AllActive();
	}

	//すべてのオブジェクトを非アクティブ化
	void AllInactive()
	{
		m_objectManager->AllInactive();
	}

	//ポストエフェクトを取得
	CPostEffect& GetPostEffect()
	{
		return m_postEffect;
	}

	//ディファードを取得
	CDeferred& GetDeferred()
	{
		return m_deferred;
	}

	//シャドウマップを取得
	CShadowMap& GetShadowMap()
	{
		return m_shadowMap;
	}

	//アルファブレンドの設定を変更
	void SetAlphaBlendState(EnAlphaBlendState alphaBlendState)
	{
		m_alphaBlend.SetBlendState(m_pDeviceContext, alphaBlendState);
	}

	//深度の設定を変更
	void SetDepthStencilState(EnDepthStencilState depthStencilState)
	{
		m_depthState.SetDepthStencilState(m_pDeviceContext, depthStencilState);
	}

	//ラスタライザの設定を変更
	void SetRasterizerState(EnRasterizerState rasterizerState)
	{
		m_rasterizerState.SetRasterizerState(m_pDeviceContext, rasterizerState);
	}

	//ビューポートの設定を変更
	void SetViewPortState(EnViewPortState viewPortNum)
	{
		m_viewPortState.SetViewPort(m_pDeviceContext, viewPortNum);
	}

	//現在のビューポートの設定を取得
	EnViewPortState GetCurrentViewPortState()
	{
		return m_viewPortState.GetCurrentState();
	}

	//現在の深度設定を取得
	EnDepthStencilState GetCurrentDepthStencilState()
	{
		return m_depthState.GetCurrentDepthState();
	}

	EnAlphaBlendState GetCurrentAlphaBlendState()
	{
		return m_alphaBlend.GetCurrentBlendState();
	}

	//現在のラスタライザの設定を取得
	EnRasterizerState GetCurrentRasterizerState()
	{
		return m_rasterizerState.GetCurrentState();
	}

	CPointLightManager& GetPointLightManager()
	{
		return m_pointLightManager;
	}

	DirectX::SpriteBatch* GetSpriteBatch()
	{
		return m_spriteBatch.get();
	}

	CEffectEngine& GetEffectEngine()
	{
		return m_effectEngine;
	}

	CEffectResource& GetEffectResource()
	{
		return m_effectResource;
	}

	CAnimationResource& GetAnimationResource()
	{
		return m_animationResource;
	}

private:
	static const int							MAIN_RENDER_TARGET_NUM = 2;
	CGameObjectManager*							m_objectManager;			//オブジェクトマネージャー
	WNDCLASSEX									m_wc;						//ウィンドウクラス
	Microsoft::WRL::ComPtr<ID3D11Device>		m_pD3DDevice;
	int											m_frameBufferWidth;
	int											m_frameBufferHeight;
	Microsoft::WRL::ComPtr<IDXGISwapChain>		m_pSwapChain;
	D3D_FEATURE_LEVEL							m_featureLevel;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>	m_pDeviceContext;
	CRenderTarget								m_mainRenderTarget[MAIN_RENDER_TARGET_NUM];
	int											m_currentRenderTargetNum = 0;
	D3D_DRIVER_TYPE								m_driverType;
	HWND										m_hwnd;
	CPhysicsWorld*								m_physicsWorld;				//物理ワールド
	CSoundEngine*								m_soundEngine;				//サウンドエンジン]
	std::unique_ptr<CPad>						m_pad;
	CTextureResource							m_textureResource;
	CSkinmodelResource							m_skinmodelResource;
	CShaderResource								m_shaderResource;
	CEffectResource								m_effectResource;
	CAnimationResource							m_animationResource;
	CLight										m_light;
	CDeferred									m_deferred;
	CPostEffect									m_postEffect;
	CAlphaBlendState							m_alphaBlend;
	CRasterizerState							m_rasterizerState;
	CDepthStencilState							m_depthState;
	CShadowMap									m_shadowMap;
	CViewPortState								m_viewPortState;
	CPointLightManager							m_pointLightManager;
	std::unique_ptr<DirectX::SpriteBatch>		m_spriteBatch;
	CEffectEngine								m_effectEngine;
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

static CAnimationResource& AnimationResource()
{
	return Engine().GetAnimationResource();
}

static int FrameBufferWidth()
{
	return Engine().GetFrameBufferWidth();
}

static int FrameBufferHeight()
{
	return Engine().GetFrameBufferHeight();
}

static CLight& Light()
{
	return Engine().Light();
}

static CRenderTarget& MainRenderTarget()
{
	return Engine().GetMainRenderTarget();
}

