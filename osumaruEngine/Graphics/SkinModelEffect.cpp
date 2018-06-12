#include "engineStdafx.h"
#include "SkinModelEffect.h"

SkinModelEffect::SkinModelEffect()
{
	textureResource = nullptr;
	vsShader.Load("Assets/shader/model.fx", "VSSkinMain", Shader::enVS);
	psShader.Load("Assets/shader/model.fx", "PSSkinMain", Shader::enPS);
}

void __cdecl ISkinModelEffect::Apply(_In_ ID3D11DeviceContext* deviceContext)
{
	if (textureResource != nullptr)
	{
		deviceContext->PSSetShaderResources(0, 1, &textureResource);
	}
	deviceContext->PSSetShader((ID3D11PixelShader*)psShader.GetBody(), nullptr, 0);
	deviceContext->VSSetShader((ID3D11VertexShader*)vsShader.GetBody(), nullptr, 0);
}

void __cdecl ISkinModelEffect::GetVertexShaderBytecode(_Out_ void const** pShaderByteCode, _Out_ size_t* pByteCodeLength)
{
	*pShaderByteCode = vsShader.GetByteCode();
	*pByteCodeLength = vsShader.GetByteCodeSize();

}


NoSkinModelEffect::NoSkinModelEffect()
{
	textureResource = nullptr;
	vsShader.Load("Assets/shader/model.fx", "VSMain", Shader::enVS);
	psShader.Load("Assets/shader/model.fx", "PSMain", Shader::enPS);
}
