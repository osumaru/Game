#include "engineStdafx.h"
#include "SkinModelEffectFactory.h"
#include "SkinModelEffect.h"

std::shared_ptr<DirectX::IEffect> __cdecl CSkinModelEffectFactory::CreateEffect(_In_ const IEffectFactory::EffectInfo& info, _In_opt_ ID3D11DeviceContext* deviceContext)
{
	std::shared_ptr<ISkinModelEffect> effect;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> view;
	//スキン有りのモデルとスキン無しのモデルでエフェクトを分ける
	if (info.enableSkinning)
	{
		effect = std::make_shared<CSkinModelEffect>();
	}
	else
	{
		effect = std::make_shared<CNoSkinModelEffect>();
	}
	//テクスチャがある場合は作る
	if (info.diffuseTexture != nullptr)
	{
		wchar_t filePath[256];
		swprintf(filePath, L"Assets/modelData/%s", info.diffuseTexture);
		CreateTexture(filePath, GetDeviceContext(), view.ReleaseAndGetAddressOf());
		effect->SetTexture(view);
	}
	return effect;
}

void __cdecl CSkinModelEffectFactory::CreateTexture(_In_z_ const wchar_t* name, _In_opt_ ID3D11DeviceContext* deviceContext, _Outptr_ ID3D11ShaderResourceView** textureView)
{
	EffectFactory::CreateTexture(name, deviceContext, textureView);
}
