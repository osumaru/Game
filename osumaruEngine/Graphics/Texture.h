#pragma once
//テクスチャクラス

class CTexture : Uncopyable
{
public:
	//レンダリングターゲットの種類
	enum EnTextureType
	{
		enRendertarget,		//レンダリングターゲット
		enDepthStencil,		//デプスステンシルバッファ
	};
	//コンストラクタ
	CTexture();

	//デストラクタ
	~CTexture();

	/*
	テクスチャの読み込み関数
	filepath テクスチャがあるファイルのパス
	*/
	void Load(const wchar_t* filepath);

	/*
	テクスチャを作る関数
	*/
	void Create(int width, int height, EnTextureType textureType, DXGI_FORMAT format);

	//テクスチャを取得
	Microsoft::WRL::ComPtr<ID3D11Resource> GetTexture()
	{
		return m_pTexture;
	}

	//テクスチャを取得
	Microsoft::WRL::ComPtr<ID3D11Texture2D> GetTexture2D()
	{
		return m_pTexture2D;
	}

	//シェーダーリソースビューを取得
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& GetShaderResource()
	{
		return m_pShaderResource;
	}

	Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView>& GetUnorderedAccessView()
	{
		return m_pUnorderedAccess;
	}

	//テクスチャの横幅を取得
	int GetWidth() const
	{
		return m_width;
	}

	//テクスチャの縦幅を取得
	int GetHeight() const
	{
		return m_height;
	}

private:
	int														m_width;			//テクスチャの横幅									
	int														m_height;			//テクスチャの縦幅
	Microsoft::WRL::ComPtr<ID3D11Resource>					m_pTexture;			//テクスチャ
	Microsoft::WRL::ComPtr<ID3D11Texture2D>					m_pTexture2D;			//テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_pShaderResource;	//SRV
	Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView>		m_pUnorderedAccess;	//UAV
};