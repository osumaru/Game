#pragma once
#pragma once
#include "GameObject/GameObjectManager.h"
#include "Graphics/Texture.h"
#include "Graphics\RenderTarget.h"
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

	int GetFrameBufferWidth()
	{
		return m_frameBufferWidth;
	}

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

	ID3D11Device* GetDevice()
	{
		return m_pD3DDevice;
	}
	
	ID3D11DeviceContext* GetDeviceContext()
	{
		return m_pDeviceContext;
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


private:

	CGameObjectManager						m_objectManager;			//�I�u�W�F�N�g�}�l�[�W���[
	WNDCLASSEX								m_wc;						//�E�B���h�E�N���X
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
	std::unique_ptr<CPhysicsWorld>			m_physicsWorld;				//�������[���h
	std::unique_ptr<CSoundEngine>			m_soundEngine;				//�T�E���h�G���W��]
	std::unique_ptr<CPad>					m_pad;
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
	return GetEngine().New<T, TArgs...>(priority, args...);
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

