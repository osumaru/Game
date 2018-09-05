#pragma once

//エフェクトファクトリー
class CSkinModelEffectFactory : public EffectFactory
{
public:
	//コンストラクタ
	CSkinModelEffectFactory(_In_ ID3D11Device* device) :
		EffectFactory(device)
	{
	}
	/*
	エフェクトを作る関数
	info	モデルなどの情報
	*/
	std::shared_ptr<IEffect> __cdecl CreateEffect(_In_ const IEffectFactory::EffectInfo& info, _In_opt_ ID3D11DeviceContext* deviceContext)override;

	/*
	テクスチャを作る関数
	name		テクスチャのファイル名
	*/
	void __cdecl CreateTexture(_In_z_ const wchar_t* name, _In_opt_ ID3D11DeviceContext* deviceContext, _Outptr_ ID3D11ShaderResourceView** textureView)override;
private:
};