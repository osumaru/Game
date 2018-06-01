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
	ConstantBuffer constantBuffer;
	Shader vsShader;
	Shader psShader;
};

class SkinModelEffect : public ISkinModelEffect
{
public:

	SkinModelEffect();


private:
};


class NoSkinModelEffect : public ISkinModelEffect
{
public:

	NoSkinModelEffect();

private:
};
