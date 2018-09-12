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
	ID3D11DeviceChild* GetBody()const
	{
		return m_pShader;
	}

	//頂点レイアウトを取得
	ID3D11InputLayout* GetInputlayOut() const
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

	//ホットリロード用の関数
	void ReLoad();

	void EraseFlgFold()
	{
		m_isErase = false;
	}
private:
	ID3D11DeviceChild*				m_pShader;			//シェーダー
	ID3D11InputLayout*				m_pInputLayout;		//頂点レイアウト
	ID3DBlob*						m_blob;				//シェーダーデータ
	const char*						m_filePath;
	const char*						m_entryFuncName;
	EnShaderType					m_shaderType;
	std::list<CShader*>::iterator	m_it;
	bool							m_isErase;
};