#include "engineStdafx.h"
#include "SamplerState.h"


void CSamplerState::Init(EnSamplerAddressingMode addressingMode, EnSamplerFilter filter)
{
	D3D11_SAMPLER_DESC desc;
	desc.MinLOD = 0.0f;
	desc.MaxLOD = 0.0f;
	desc.MipLODBias = 0.0f;
	desc.MaxAnisotropy = 16;
	desc.BorderColor[0] = 1.0f;
	desc.BorderColor[1] = 1.0f;
	desc.BorderColor[2] = 1.0f;
	desc.BorderColor[3] = 1.0f;
	desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	D3D11_TEXTURE_ADDRESS_MODE addMode;
	switch (addressingMode)
	{
	case enAddressingModeClamp:
		addMode = D3D11_TEXTURE_ADDRESS_CLAMP;
		break;

	case enAddressingModeWrap:
		addMode = D3D11_TEXTURE_ADDRESS_WRAP;
		break;
	}
	desc.AddressU = addMode;
	desc.AddressV = addMode;
	desc.AddressW = addMode;
	switch (filter)
	{
	case enFilterLinear:
		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		break;
	case enFilterTest:
		desc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT;
		break;
	}
	GetDevice()->CreateSamplerState(&desc,& m_samplerState);

}
