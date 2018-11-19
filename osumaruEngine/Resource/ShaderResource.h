#pragma once
#include "../Graphics/Shader.h"

struct SShaderResource
{
	Microsoft::WRL::ComPtr<ID3D11DeviceChild>		m_pShader;			//シェーダー
	Microsoft::WRL::ComPtr<ID3D11InputLayout>		m_pInputLayout;		//頂点レイアウト
	Microsoft::WRL::ComPtr<ID3DBlob>				m_blob;				//シェーダーのバッファ
	char*											entryFuncName;		//関数名(リロード時に使う)
	char*											fileName;			//ファイル名(リロード時に使う)
	CShader::EnShaderType							shaderType;			//シェーダーの種類(リロード時に使う)
};

struct SShaderData
{
	char*			data;		//シェーダーデータ
	int				filepos;	//ファイルサイズ
	char*			fileName;	//ファイル名(リロード時に使う)
};

//シェーダーリソースを管理するクラス
class CShaderResource : Uncopyable
{
public:
	//デストラクタ
	~CShaderResource();

	/*
	filePath	ファイルパス
	ret　シェーダーのファイルを読み込んだデータ
	*/
	SShaderData ReadFile(const char* filePath);

	/*
	エフェクトファイルを読み込む関数
	filepath		ファイルパス
	entryFuncName	関数の名前
	shaderType		シェーダーの種類
	ret				シェーダーのバッファ、シェーダー、頂点レイアウト
	*/
	SShaderResource Load(const char* filepath, const char* entryFuncName, CShader::EnShaderType shaderType);

	//シェーダーファイルを全部再コンパイル
	void ReLoad();

	//リロードするシェーダーリストに登録
	std::list<CShader*>::iterator ShaderPushBack(CShader* shader);

	//リロードするシェーダーリストから削除
	void ShaderErase(std::list<CShader*>::iterator it);
private:

	//頂点レイアウトを作る関数
	void CreateInputLayout(Microsoft::WRL::ComPtr<ID3DBlob> blob, ID3D11InputLayout** inputLayout);
private:

	std::map<int, SShaderData>		m_shaderData;			//シェーダーのデータ
	std::map<int, SShaderResource>	m_shaderResource;		//シェーダーの
	std::list<CShader*>				m_shaders;				//リロード用のシェーダーリスト
};