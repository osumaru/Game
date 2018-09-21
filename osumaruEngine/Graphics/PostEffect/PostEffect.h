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

	void Init(IDXGISwapChain* swapChain);

	void Draw();
private:
	CPrimitive								m_primitive;
	CShader									m_vertexShader;		//���_�V�F�[�_�[
	CShader									m_pixelShader;		//�s�N�Z���V�F�[�_�[
	CTexture								m_depthStencilTexture;
	CRenderTarget							m_backBuffer;
	ID3D11RenderTargetView*					m_pBackBuffer;
	ID3D11DepthStencilView*					m_depthStencil;
};