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
	pRenderTarget	�����_�����O�^�[�Q�b�g�Ɏg���e�N�X�`��
	pDepthStencil	�f�v�X�X�e���V���o�b�t�@�Ɏg���e�N�X�`��
	width			�����_�����O�^�[�Q�b�g�̕�
	height			�����_�����O�^�[�Q�b�g�̍���
	isBackBuffer	�o�b�N�o�b�t�@���ǂ���
	*/
	void Create(ID3D11Texture2D* pRenderTarget, ID3D11Texture2D* pDepthStencil, int width, int height, bool isBackBuffer);

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
		return m_pRenderTargetTexture;
	}


	//�f�v�X�X�e���V���e�N�X�`��
	ID3D11Texture2D* GetDepthStencilTexture() const
	{
		return m_pDepthStencilTexture;
	}
private:
	ID3D11DepthStencilView*					m_pDepthStencil;		//�f�v�X�X�e���V���r���[
	ID3D11RenderTargetView*					m_pRenderTarget;		//�����_�����O�^�[�Q�b�g
	ID3D11Texture2D*						m_pRenderTargetTexture;	//�����_�����O�^�[�Q�b�g�p�̃e�N�X�`��	
	ID3D11Texture2D*						m_pDepthStencilTexture;	//�f�v�X�X�e���V���p�̃e�N�X�`��
	int										m_width;				//�����_�����O�^�[�Q�b�g�̕�
	int										m_height;				//�����_�����O�^�[�Q�b�g�̍���
};
