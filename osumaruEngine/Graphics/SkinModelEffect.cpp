#include "engineStdafx.h"
#include "SkinModelEffect.h"

CSkinModelEffect::CSkinModelEffect()
{
	textureResource = nullptr;
	vsShader.Load("Assets/shader/model.fx", "VSSkinMain", CShader::enVS);
	psShader.Load("Assets/shader/model.fx", "PSMain", CShader::enPS);
}

void __cdecl ISkinModelEffect::Apply(_In_ ID3D11DeviceContext* deviceContext)
{
	//シェーダーを適用
	if (textureResource != nullptr)
	{
		deviceContext->PSSetShaderResources(10, 1, &textureResource);
	}
	deviceContext->PSSetShader((ID3D11PixelShader*)psShader.GetBody(), nullptr, 0);
	deviceContext->VSSetShader((ID3D11VertexShader*)vsShader.GetBody(), nullptr, 0);
}

void __cdecl ISkinModelEffect::GetVertexShaderBytecode(_Out_ void const** pShaderByteCode, _Out_ size_t* pByteCodeLength)
{
	//シェーダーデータをコピー
	*pShaderByteCode = vsShader.GetByteCode();
	*pByteCodeLength = vsShader.GetByteCodeSize();
}


CNoSkinModelEffect::CNoSkinModelEffect()
{
	textureResource = nullptr;
	vsShader.Load("Assets/shader/model.fx", "VSMain", CShader::enVS);
	psShader.Load("Assets/shader/model.fx", "PSMain", CShader::enPS);
}
