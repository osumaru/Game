#include "MotionBlur.h"


void CMotionBlur::Init()
{
	m_vs.Load("Assets/shader/MotionBlur.fx", "VSMain", CShader::enVS);
	m_ps.Load("Assets/shader/MotionBlur.fx", "PSMain", CShader::enPS);
	SVSLayout vertexBufferLayout[4] =
	{
		{ { -1.0f,  1.0f, 1.0f, 1.0f } , { 0.0f, 0.0f } },
		{ {  1.0f,  1.0f, 1.0f, 1.0f } , { 1.0f, 0.0f } },
		{ { -1.0f, -1.0f, 1.0f, 1.0f } , { 0.0f, 1.0f } },
		{ {  1.0f, -1.0f, 1.0f, 1.0f } , { 1.0f, 1.0f } },
	};
	DWORD indexBufferLayout[4] = { 0, 2, 1, 3 };
	m_primitive.Create(vertexBufferLayout, sizeof(SVSLayout), 4, indexBufferLayout, 4, CPrimitive::enIndex32, CPrimitive::enTypeTriangleStrip);
	
	m_sampler.Init(EnSamplerAddressingMode::enAddressingModeClamp, EnSamplerFilter::enFilterLinear);
}

void CMotionBlur::Update()
{

}

void CMotionBlur::Draw()
{
	float color[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
	ID3D11ShaderResourceView* srviews[] = {
		MainRenderTarget().GetRenderTargetTexture().GetShaderResource().Get(),
		Engine().GetDeferred().GetShaderResource(enRenderTargetVelocity).Get()};
	Engine().SwitchingRenderTarget();
	GetDeviceContext()->OMSetRenderTargets(1, MainRenderTarget().GetRenderTarget().GetAddressOf(), MainRenderTarget().GetDepthStencil().Get());
	GetDeviceContext()->ClearRenderTargetView(MainRenderTarget().GetRenderTarget().Get(), color);
	GetDeviceContext()->ClearDepthStencilView(MainRenderTarget().GetDepthStencil().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	Engine().SetAlphaBlendState(enAlphaBlendStateNone);
	Engine().SetDepthStencilState(enDepthStencilState2D);
	Engine().SetRasterizerState(enRasterizerState2D);
	GetDeviceContext()->PSSetShaderResources(0, 2, srviews);
	GetDeviceContext()->VSSetShader((ID3D11VertexShader*)m_vs.GetBody().Get(), nullptr, 0);
	GetDeviceContext()->PSSetShader((ID3D11PixelShader*)m_ps.GetBody().Get(), nullptr, 0);
	GetDeviceContext()->IASetInputLayout(m_vs.GetInputlayOut().Get());
	ID3D11SamplerState* samplerStates[] = {m_sampler.GetBody()};
	GetDeviceContext()->PSSetSamplers(1, 1, samplerStates);
	m_primitive.Draw(GetDeviceContext());
}