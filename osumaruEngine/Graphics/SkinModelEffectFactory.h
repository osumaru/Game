#pragma once
class SkinModelEffectFactory : public EffectFactory
{
public:
	SkinModelEffectFactory(_In_ ID3D11Device* device) :
		EffectFactory(device)
	{
	}
	std::shared_ptr<IEffect> __cdecl CreateEffect(_In_ const IEffectFactory::EffectInfo& info, _In_opt_ ID3D11DeviceContext* deviceContext)override;

	void __cdecl CreateTexture(_In_z_ const wchar_t* name, _In_opt_ ID3D11DeviceContext* deviceContext, _Outptr_ ID3D11ShaderResourceView** textureView)override;
private:
};