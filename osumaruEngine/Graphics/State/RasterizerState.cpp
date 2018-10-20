#include "engineStdafx.h"
#include "RasterizerState.h"


void CRasterizerState::Init(ID3D11Device* device)
{
	D3D11_RASTERIZER_DESC rasterizerDesc;
	ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_FRONT;
	device->CreateRasterizerState(&rasterizerDesc, &m_rasterizerState[enRasterizerState2D]);
	device->CreateRasterizerState(&rasterizerDesc, &m_rasterizerState[enRasterizerState3D]);
}
