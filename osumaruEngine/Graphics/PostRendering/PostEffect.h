#pragma once
#include "Bloom.h"
#include "MotionBlur.h"

class CPostEffect
{
public:
	//���_���C�A�E�g
	struct SVSLayout
	{
		CVector4 position;
		CVector2	uv;
	};

	~CPostEffect();

	/*
	�������֐�
	swapChain		�o�b�N�o�b�t�@�擾�p�̃X���b�v�`�F�C���C���X�^���X
	*/
	void Init(Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain);

	//�`��֐�
	void Draw();

	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> GetDepthStencil()
	{
		return m_pBackDepthStencilView;
	}

	CBloom& GetBloom()
	{
		return m_bloom;
	}

private:
	CBloom											m_bloom;
	CMotionBlur										m_motionBlur;
	CPrimitive										m_primitive;			//�v���~�e�B�u
	CShader											m_vertexShader;			//���_�V�F�[�_�[
	CShader											m_pixelShader;			//�s�N�Z���V�F�[�_�[
	CRenderTarget									m_backBuffer;			//�o�b�N�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	m_pBackRenderTargetView = nullptr;//�o�b�N�o�b�t�@��RTV
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView>	m_pBackDepthStencilView = nullptr;//�o�b�N�o�b�t�@��DSV
};