#include "engineStdafx.h"
#include "RasterizerState.h"


void CRasterizerState::Init(Microsoft::WRL::ComPtr<ID3D11Device> device)
{
	D3D11_RASTERIZER_DESC rasterizerDesc;
	ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_FRONT;
	device->CreateRasterizerState(&rasterizerDesc, &m_rasterizerState[enRasterizerState2D]);
	device->CreateRasterizerState(&rasterizerDesc, &m_rasterizerState[enRasterizerState3D]);
	rasterizerDesc.CullMode = D3D11_CULL_NONE;
	device->CreateRasterizerState(&rasterizerDesc, &m_rasterizerState[enRasterizerStateBoth]);
}
