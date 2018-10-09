#include "engineStdafx.h"
#include "AlphaBlendState.h"

CAlphaBlendState::~CAlphaBlendState()
{
	for (int i = 0; i < enAlphaBlendStateNum; i++)
	{
		if (m_blendState[i] != nullptr)
		{
			m_blendState[i]->Release();
		}
	}
}

void CAlphaBlendState::Init(ID3D11Device* device)
{
	D3D11_BLEND_DESC blendDesc;
	blendDesc.AlphaToCoverageEnable = false;
	blendDesc.IndependentBlendEnable = false;
	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_COLOR;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_DEST_COLOR;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	device->CreateBlendState(&blendDesc, &m_blendState[enAlphaBlendState2D]);

	blendDesc.RenderTarget[0].BlendEnable = false;
	device->CreateBlendState(&blendDesc, &m_blendState[enAlphaBlendState3D]);

}
