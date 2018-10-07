#pragma once
#pragma once
#include "GameObject/GameObjectManager.h"
#include "Graphics/Texture.h"
#include "Graphics\RenderTarget.h"
#include "Resource/TextureResource.h"
#include "Resource/SkinmodelResource.h"
#include "Resource/ShaderResource.h"
#include "Graphics/Primitive.h"
#include "Graphics/Light.h"
#include "Graphics/ConstantBuffer.h"
#include "Graphics/PostEffect/Deferred.h"
#include "Graphics/State/AlphaBlendState.h"
#include "Graphics/State/DepthStencilState.h"
#include "Graphics/State/RasterizerState.h"


//�G���W���N���X


class CEffectManager;
class CGameObject;
class CPhysicsWorld;
class CSoundEngine;
class CPad;

class CEngine
{
private:
	//�R���X�g���N�^�B�V���O���g���̂��߃v���C�x�[�g�ɂȂ��Ă���
	CEngine();

	//�f�X�g���N�^�B�V���O���g���̂��߃v���C�x�[�g�ɂȂ��Ă���
	~CEngine();
public:
	//���_���C�A�E�g
	struct SVSLayout
	{
		CVector4 position;
		CVector2	uv;
	};

	//DirectX��������
	void InitD3D(HINSTANCE& hInst);

	//�Q�[�����[�v
	void GameLoop();

	//�����̃C���X�^���X���擾
	static CEngine& GetEngine()
	{
		static CEngine engine;
		return engine;
	}
	//�����[�X
	void Release()
	{

	}

	//�t���[���o�b�t�@�̉������擾
	int GetFrameBufferWidth()
	{
		return m_frameBufferWidth;
	}

	//�t���[���o�b�t�@�̏c�����擾
	int GetFrameBufferHeight()
	{
		return m_frameBufferHeight;
	}

	//�������[���h���擾�B
	CPhysicsWorld& PhysicsWorld()
	{
		return *m_physicsWorld;
	}

	//�T�E���h�G���W�����擾
	CSoundEngine& SoundEngine()
	{
		return *m_soundEngine;
	}

	//�p�b�h�̎擾
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

	ID3D11ShaderResourceView* GetShaderResource(EnRenderTarget numRenderTarget)
	{
		return  m_deferred.GetShaderResource(numRenderTarget);
	}

	//�C���X�^���X�̐���
	template<class T, class... TArgs>
	T* New(int priority, TArgs... args)
	{
		return m_objectManager.New<T, TArgs...>(priority, args...);
	}

	//�C���X�^���X�̍폜
	void Delete(IGameObject* deleteObject)
	{
		m_objectManager.Delete(deleteObject);
	}

	//�C���X�^���X���I�u�W�F�N�g�}�l�[�W���[�ɓo�^
	void Add(IGameObject* object, int priority)
	{
		m_objectManager.Add(object, priority);
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

	//���ׂẴI�u�W�F�N�g���A�N�e�B�u��
	void AllActive()
	{
		m_objectManager.AllActive();
	}

	//���ׂẴI�u�W�F�N�g���A�N�e�B�u��
	void AllInactive()
	{
		m_objectManager.AllInactive();
	}

private:
	static const int						MAIN_RENDER_TARGET_NUM = 2;
	CGameObjectManager						m_objectManager;			//�I�u�W�F�N�g�}�l�[�W���[
	WNDCLASSEX								m_wc;						//�E�B���h�E�N���X
	ID3D11Device*							m_pD3DDevice;
	int										m_frameBufferWidth;
	int										m_frameBufferHeight;
	IDXGISwapChain*							m_pSwapChain;
	D3D_FEATURE_LEVEL						m_featureLevel;
	ID3D11DeviceContext*					m_pDeviceContext;
	CRenderTarget							m_mainRenderTarget[MAIN_RENDER_TARGET_NUM];
	int										m_currentRenderTargetNum = 0;
	D3D_DRIVER_TYPE							m_driverType;
	HWND									m_hwnd;
	std::unique_ptr<CPhysicsWorld>			m_physicsWorld;				//�������[���h
	std::unique_ptr<CSoundEngine>			m_soundEngine;				//�T�E���h�G���W��]
	std::unique_ptr<CPad>					m_pad;
	CTextureResource						m_textureResource;
	CSkinmodelResource						m_skinmodelResource;
	CShaderResource							m_shaderResource;
	CLight									m_light;
	Deferred								m_deferred;
	PostEffect								m_postEffect;
	CAlphaBlendState						m_alphaBlend;
	CRasterizerState						m_rasterizerState;
	CDepthStencilState						m_depthState;
};

//�G���W���N���X�̃C���X�^���X���擾�B
static CEngine& Engine()
{
	return CEngine::GetEngine();
}

//�C���X�^���X�̐���
template <class T, class... TArgs>
static T* New(int priority, TArgs... args)
{
	return Engine().New<T, TArgs...>(priority, args...);
}
//�C���X�^���X�̍폜
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

//�p�b�h�̎擾
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

static CLight& Light()
{
	return Engine().Light();
}

static CRenderTarget& MainRenderTarget()
{
	return Engine().GetMainRenderTarget();
}
