#include "engineStdafx.h"
#include "DepthStencilState.h"


CDepthStencilState::~CDepthStencilState()
{
	for (int i = 0; i < enDepthStencilStateNum; i++)
	{
		if (m_depthStencilState[i] != nullptr)
		{
			m_depthStencilState[i]->Release();
		}
	}
}

void CDepthStencilState::Init(Microsoft::WRL::ComPtr<ID3D11Device> device)
{

	D3D11_DEPTH_STENCIL_DESC depthDesc;
	ZeroMemory(&depthDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));

	depthDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	depthDesc.DepthEnable = true;
	depthDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	device->CreateDepthStencilState(&depthDesc, &m_depthStencilState[enDepthStencilState3D]);
	depthDesc.DepthEnable = false; 
	device->CreateDepthStencilState(&depthDesc, &m_depthStencilState[enDepthStencilState2D]);
}