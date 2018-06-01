#pragma once
#pragma once
#include "GameObject/GameObjectManager.h"
#include "Graphics/Texture.h"
#include "Graphics\RenderTarget.h"

//�G���W���N���X

const int FRAME_BUFFER_WIDTH = 1280;
const int FRAME_BUFFER_HEIGHT = 720;

class EffectManager;
class GameObject;


class Engine
{
private:
	//�R���X�g���N�^�B�V���O���g���̂��߃v���C�x�[�g�ɂȂ��Ă���
	Engine();

	//�f�X�g���N�^�B�V���O���g���̂��߃v���C�x�[�g�ɂȂ��Ă���
	~Engine();
public:
	//DirectX��������
	void InitD3D(HINSTANCE& hInst);

	//�Q�[�����[�v
	void GameLoop();

	//�����̃C���X�^���X���擾
	static Engine& GetEngine()
	{
		static Engine engine;
		return engine;
	}
	//�����[�X
	void Release()
	{

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
	void Delete(GameObject* deleteObject)
	{
		m_objectManager.Delete(deleteObject);
	}

	//�C���X�^���X���I�u�W�F�N�g�}�l�[�W���[�ɓo�^
	void Add(GameObject* object, int priority)
	{
		m_objectManager.Add(object, priority);
	}


private:

	GameObjectManager						m_objectManager;			//�I�u�W�F�N�g�}�l�[�W���[
	WNDCLASSEX								m_wc;						//�E�B���h�E�N���X
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
};

//�G���W���N���X�̃C���X�^���X���擾�B
static Engine& GetEngine()
{
	return Engine::GetEngine();
}

//�C���X�^���X�̐���
template <class T, class... TArgs>
static T* New(int priority, TArgs... args)
{
	return GetEngine().New<T, TArgs...>(priority, args...);
}
//�C���X�^���X�̍폜
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


