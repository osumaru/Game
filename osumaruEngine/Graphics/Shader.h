#pragma once
//シェーダー(エフェクトファイル)を読み込むクラス

class CShader : Uncopyable
{
public:
	//コンストラクタ
	CShader();

	//デストラクタ
	~CShader();

	//シェーダーの種類
	enum EnShaderType
	{
		enVS,		//頂点シェーダー
		enPS,		//ピクセルシェーダー
		enCS,		//コンピュートシェーダー
	};

	/*
	エフェクトファイルを読み込む関数
	filepath		ファイルパス
	entryFuncName	関数の名前
	shaderType		シェーダーの種類
	*/
	void Load(const char* filepath, const char* entryFuncName, EnShaderType shaderType);

	//シェーダーを取得
	ID3D11DeviceChild* GetBody()
	{
		return m_pShader;
	}

	//頂点レイアウトを取得
	ID3D11InputLayout* GetInputlayOut()
	{
		return m_pInputLayout;
	}

	//シェーダーデータを取得
	void* GetByteCode()
	{
		return m_blob->GetBufferPointer();
	}
	//シェーダーデータのサイズを取得。
	size_t GetByteCodeSize()
	{
		return m_blob->GetBufferSize();
	}

private:

	//頂点レイアウトを作る関数
	void CreateInputLayout(ID3DBlob* blob);

private:
	std::unique_ptr<char[]>			m_pShaderData;		//シェーダーをコンパイルしたデータを格納するバッファ
	ID3D11DeviceChild*				m_pShader;			//シェーダー
	ID3D11InputLayout*				m_pInputLayout;		//頂点レイアウト
	ID3DBlob*						m_blob;				//シェーダーデータ
};