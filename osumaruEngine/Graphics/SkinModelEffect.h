#pragma once

class ISkinModelEffect : public DirectX::IEffect
{
public:

	ISkinModelEffect()
	{

	}

	void __cdecl Apply(_In_ ID3D11DeviceContext* deviceContext)override;

	void __cdecl GetVertexShaderBytecode(_Out_ void const** pShaderByteCode, _Out_ size_t* pByteCodeLength)override;

	void SetTexture(ID3D11ShaderResourceView* texture)
	{
		textureResource = texture;
	}

protected:
	ID3D11ShaderResourceView* textureResource;
	CConstantBuffer constantBuffer;
	CShader vsShader;
	CShader psShader;
};

class CSkinModelEffect : public ISkinModelEffect
{
public:

	CSkinModelEffect();


private:
};


class CNoSkinModelEffect : public ISkinModelEffect
{
public:

	CNoSkinModelEffect();

private:
};
