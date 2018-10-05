#include "engineStdafx.h"
#include "Deferred.h"

Deferred::Deferred()
{

}

void Deferred::Init()
{
	for (int i = 0; i < enRenderTargetNum; i++)
	{
		m_renderTarget[i].Create(FrameBufferWidth(), FrameBufferHeight());
	}
	m_lightCB.Create(sizeof(CLight), &Light());
	m_vertexShader.Load("Assets/shader/deferred.fx", "VSMain", CShader::enVS);
	m_pixelShader.Load("Assets/shader/deferred.fx", "PSMain", CShader::enPS);
	SVSLayout vertexBufferLayout[4] =
	{
		{ { -1.0f,  1.0f, 0.0f, 1.0f } , { 0.0f, 0.0f } },
		{ {  1.0f,  1.0f, 0.0f, 1.0f } , { 1.0f, 0.0f } },
		{ { -1.0f, -1.0f, 0.0f, 1.0f } , { 0.0f, 1.0f } },
		{ {  1.0f, -1.0f, 0.0f, 1.0f } , { 1.0f, 1.0f } },
	};
	DWORD indexBufferLayout[4] = { 0, 2, 1, 3 };
	m_primitive.Create(vertexBufferLayout, sizeof(SVSLayout), 4, indexBufferLayout, 4, CPrimitive::enIndex32, CPrimitive::enTypeTriangleStrip);
}

void Deferred::Start()
{
	float color[4] = { 0.0f, 0.0f, 1.0f, 0.0f };

	float depthColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	ID3D11RenderTargetView* mainViews[enRenderTargetNum];
	for (int i = 0; i < enRenderTargetNum;i++)
	{
		mainViews[i] = m_renderTarget[i].GetRenderTarget();
	};

	GetDeviceContext()->OMSetRenderTargets(enRenderTargetNum, mainViews, m_renderTarget[0].GetDepthStencil());
	for (int i = 0; i < enRenderTargetNum; i++)
	{
		if (i == enRenderTargetDepth)
		{
			GetDeviceContext()->ClearRenderTargetView(m_renderTarget[i].GetRenderTarget(), depthColor);
		}
		else
		{
			GetDeviceContext()->ClearRenderTargetView(m_renderTarget[i].GetRenderTarget(), color);
		}
	}
	GetDeviceContext()->ClearDepthStencilView(m_renderTarget[0].GetDepthStencil(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	m_lightCB.Create(sizeof(CLight), &Light());
}

void Deferred::Draw()
{
	float color[4] = { 0.0f, 0.0f, 1.0f, 0.0f };
	ID3D11RenderTargetView* backBuffer[] = { MainRenderTarget().GetRenderTarget() };
	GetDeviceContext()->OMSetRenderTargets(1, backBuffer, MainRenderTarget().GetDepthStencil());

	GetDeviceContext()->ClearRenderTargetView(backBuffer[0], color);
	GetDeviceContext()->ClearDepthStencilView(MainRenderTarget().GetDepthStencil(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	ID3D11ShaderResourceView* srviews[enRenderTargetNum];
	for (int i = 0; i < enRenderTargetNum; i++)
	{
		srviews[i] = m_renderTarget[i].GetRenderTargetTexture().GetShaderResource();
	};
	CLight light = Light();
	m_lightCB.Update(&Light());
	ID3D11Buffer* buffer = m_lightCB.GetBody();
	GetDeviceContext()->PSSetConstantBuffers(0, 1, &buffer);
	GetDeviceContext()->PSSetShaderResources(0, enRenderTargetNum, srviews);
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
}
