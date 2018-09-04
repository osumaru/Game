#pragma once
//テクスチャクラス

class CTexture : Uncopyable
{
public:
	enum EnTextureType
	{
		enRendertarget,
		enDepthStencil,
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
	ID3D11Resource* GetTexture()
	{
		return m_pTexture;
	}

	//シェーダーリソースビューを取得
	ID3D11ShaderResourceView* GetShaderResource()
	{
		return m_pShaderResource;
	}

	//テクスチャの横幅を取得
	int GetWidth()
	{
		return m_width;
	}

	//テクスチャの縦幅を取得
	int GetHeight()
	{
		return m_height;
	}

private:
	int m_width;
	int m_height;

	ID3D11Resource*					m_pTexture;
	ID3D11ShaderResourceView*		m_pShaderResource;
};