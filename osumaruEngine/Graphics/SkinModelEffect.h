#pragma once
/*
エフェクトの規定クラス
*/
class ISkinModelEffect : public DirectX::IEffect
{
public:
	//コンストラクタ
	ISkinModelEffect()
	{

	}

	/*
	シェーダーを適用
	deviceContext	デバイスコンテキスト
	*/
	void __cdecl Apply(_In_ ID3D11DeviceContext* deviceContext)override;

	/*
	頂点シェーダーのデータを取得
	pShaderByteCode		データを格納するポインタ
	pByteCodeLength		シェーダのデータのサイズ超を格納するポインタ
	*/
	void __cdecl GetVertexShaderBytecode(_Out_ void const** pShaderByteCode, _Out_ size_t* pByteCodeLength)override;

	/*
	テクスチャを設定
	texture	テクスチャのSRV
	*/
	void SetTexture(ID3D11ShaderResourceView* texture)
	{
		textureResource = texture;
	}

protected:
	ID3D11ShaderResourceView*		textureResource;	//テクスチャのSRV
	CConstantBuffer					constantBuffer;		//定数バッファ
	CShader							vsShader;			//頂点シェーダー
	CShader							psShader;			//ピクセルシェーダー
};

//スキン有りモデルのエフェクト
class CSkinModelEffect : public ISkinModelEffect
{
public:
	//コンストラクタ
	CSkinModelEffect();


private:
};

//スキン無しモデルのエフェクト
class CNoSkinModelEffect : public ISkinModelEffect
{
public:
	//コンストラクタ
	CNoSkinModelEffect();

private:
};
