#pragma once
#include "Texture.h"
//�����_�����O�^�[�Q�b�g�N���X

class CRenderTarget : Uncopyable
{
public:
	//�R���X�g���N�^
	CRenderTarget();

	//�f�X�g���N�^
	~CRenderTarget();

	/*
	�����_�����O�^�[�Q�b�g�̍쐬
	width			�����_�����O�^�[�Q�b�g�̕�
	height			�����_�����O�^�[�Q�b�g�̍���
	format			�e�N�X�`���̃t�H�[�}�b�g
	pRenderTarget	�����_�����O�^�[�Q�b�g�Ɏg���e�N�X�`��
	*/
	void CreateRenderTarget(int width, int height, DXGI_FORMAT format, ID3D11Texture2D* pRenderTarget = nullptr);


	/*
	�f�v�X�X�e���V���o�b�t�@�̍쐬
	width			�����_�����O�^�[�Q�b�g�̕�
	height			�����_�����O�^�[�Q�b�g�̍���
	format			�e�N�X�`���̃t�H�[�}�b�g
	pRenderTarget	�����_�����O�^�[�Q�b�g�Ɏg���e�N�X�`��
	*/
	void CreateDepthStencilBuffer(int width, int height);

	//�����_�����O�^�[�Q�b�g�̎擾
	ID3D11RenderTargetView* GetRenderTarget() const
	{
		return m_pRenderTarget;
	}

	//�f�v�X�X�e���V���o�b�t�@�̎擾
	ID3D11DepthStencilView* GetDepthStencil() const
	{
		return m_pDepthStencil;
	}

	//�����_�����O�^�[�Q�b�g�p�̃e�N�X�`���̎擾
	ID3D11Texture2D* GetRenderTargetTexture() const
	{
		return m_pD3DRenderTargetTexture;
	}


	//�f�v�X�X�e���V���e�N�X�`��
	ID3D11Texture2D* GetDepthStencilTexture() const
	{
		return m_pD3DDepthStencilTexture;
	}

	//�����_�����O�^�[�Q�b�g�̃e�N�X�`�����擾
	CTexture& GetRenderTargetTexture()
	{
		return *m_pRenderTargetTexture;
	}

	//�f�v�X�X�e���V���o�b�t�@�̃e�N�X�`�����擾
	CTexture& GetDepthStencilTexture()
	{
		return *m_pDepthStencilTexture;
	}
private:
	ID3D11DepthStencilView*					m_pDepthStencil;		//�f�v�X�X�e���V���r���[
	ID3D11RenderTargetView*					m_pRenderTarget;		//�����_�����O�^�[�Q�b�g
	ID3D11Texture2D*						m_pD3DRenderTargetTexture;	//�����_�����O�^�[�Q�b�g�p�̃e�N�X�`��
	ID3D11Texture2D*						m_pD3DDepthStencilTexture;	//�f�v�X�X�e���V���p�̃e�N�X�`��
	int										m_width;				//�����_�����O�^�[�Q�b�g�̕�
	int										m_height;				//�����_�����O�^�[�Q�b�g�̍���
	std::unique_ptr<CTexture>				m_pRenderTargetTexture;	//�����_�����O�^�[�Q�b�g�p�̃e�N�X�`��
	std::unique_ptr<CTexture>				m_pDepthStencilTexture;
};
