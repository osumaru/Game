#include "engineStdafx.h"
#include "PostEffect.h"

CPostEffect::~CPostEffect()
{
}

void CPostEffect::Init(IDXGISwapChain* swapChain)
{
	m_vertexShader.Load("Assets/shader/postEffect.fx", "VSMain", CShader::enVS);
	m_pixelShader.Load("Assets/shader/postEffect.fx", "PSMain", CShader::enPS);
	SVSLayout vertexBufferLayout[4] =
	{
		{ { -1.0f,  1.0f, 1.0f, 1.0f } , { 0.0f, 0.0f } },
		{ {  1.0f,  1.0f, 1.0f, 1.0f } , { 1.0f, 0.0f } },
		{ { -1.0f, -1.0f, 1.0f, 1.0f } , { 0.0f, 1.0f } },
		{ {  1.0f, -1.0f, 1.0f, 1.0f } , { 1.0f, 1.0f } },
	};
	DWORD indexBufferLayout[4] = { 0, 2, 1, 3 };
	m_primitive.Create(vertexBufferLayout, sizeof(SVSLayout), 4, indexBufferLayout, 4, CPrimitive::enIndex32, CPrimitive::enTypeTriangleStrip);
	ID3D11Texture2D* p_RT;
	HRESULT hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)(&p_RT));
	m_backBuffer.CreateRenderTarget(FrameBufferWidth(), FrameBufferHeight(), DXGI_FORMAT_R32G32B32A32_FLOAT,  p_RT);
	m_backBuffer.CreateDepthStencilBuffer(FrameBufferWidth(), FrameBufferHeight());
	m_pBackRenderTargetView = m_backBuffer.GetRenderTarget();
	m_pBackDepthStencilView = m_backBuffer.GetDepthStencil();
}

void CPostEffect::Draw()
{
	float color[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
	GetDeviceContext()->OMSetRenderTargets(1, &m_pBackRenderTargetView, m_pBackDepthStencilView);
	GetDeviceContext()->ClearRenderTargetView(m_pBackRenderTargetView, color);
	//GetDeviceContext()->ClearDepthStencilView(m_pBackDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	Engine().SetAlphaBlendState(enAlphaBlendStateNone);
	Engine().SetDepthStencilState(enDepthStencilState2D);
	Engine().SetRasterizerState(enRasterizerState2D);
	ID3D11ShaderResourceView* srviews[] = {
		MainRenderTarget().GetRenderTargetTexture().GetShaderResource() };
	GetDeviceContext()->PSSetShaderResources(0, 1, srviews);
	GetDeviceContext()->VSSetShader((ID3D11VertexShader*)m_vertexShader.GetBody(), nullptr, 0);
	GetDeviceContext()->PSSetShader((ID3D11PixelShader*)m_pixelShader.GetBody(), nullptr, 0);
	ID3D11Buffer* vertexBuffers[] = { m_primitive.GetVertexBuffer() };
	UINT strides[] = { m_primitive.GetVertexStride() };
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, vertexBuffers, strides, &offset);
	GetDeviceContext()->IASetPrimitiveTopology(m_primitive.GetPrimitiveType());
	GetDeviceContext()->IASetIndexBuffer(m_primitive.GetIndexBuffer(), m_primitive.GetIndexFormat(), 0);
	GetDeviceContext()->IASetInputLayout(m_vertexShader.GetInputlayOut());
	GetDeviceContext()->DrawIndexed(m_primitive.GetIndexNum(), 0, 0);
	Engine().SetAlphaBlendState(enAlphaBlendStateAdd);
	Engine().SetDepthStencilState(enDepthStencilState3D);
	Engine().SetRasterizerState(enRasterizerState2D);
}