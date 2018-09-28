#pragma once

class PostEffect
{
public:
	//���_���C�A�E�g
	struct SVSLayout
	{
		CVector4 position;
		CVector2	uv;
	};

	/*
	�������֐�
	swapChain		�o�b�N�o�b�t�@�擾�p�̃X���b�v�`�F�C���C���X�^���X
	*/
	void Init(IDXGISwapChain* swapChain);

	//�`��֐�
	void Draw();

private:
	CPrimitive								m_primitive;			//�v���~�e�B�u
	CShader									m_vertexShader;			//���_�V�F�[�_�[
	CShader									m_pixelShader;			//�s�N�Z���V�F�[�_�[
	CRenderTarget							m_backBuffer;			//�o�b�N�o�b�t�@
	ID3D11RenderTargetView*					m_pBackRenderTargetView;//�o�b�N�o�b�t�@��RTV
	ID3D11DepthStencilView*					m_pBackDepthStencilView;//�o�b�N�o�b�t�@��DSV
};