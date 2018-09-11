#pragma once
#include "../Graphics/Shader.h"
struct SShaderResource
{
	ID3D11DeviceChild*				m_pShader;			//シェーダー
	ID3D11InputLayout*				m_pInputLayout;		//頂点レイアウト
	ID3DBlob*						m_blob;				//シェーダーデータ
	char*							entryFuncName;		//関数名
	char*							fileName;			//ファイル名
	CShader::EnShaderType			shaderType;			//シェーダーの種類
};

struct SShaderData
{
	char*			data;		//シェーダーデータ
	int				filepos;	//ファイルサイズ
	char*			fileName;	//ファイル名
};

class CShaderResource : Uncopyable
{
public:
	~CShaderResource();

	SShaderData ReadFile(const char* filePath);

	/*
	エフェクトファイルを読み込む関数
	filepath		ファイルパス
	entryFuncName	関数の名前
	shaderType		シェーダーの種類
	*/
	SShaderResource Load(const char* filepath, const char* entryFuncName, CShader::EnShaderType shaderType);

	//シェーダーファイルを全部再コンパイル
	void ReLoad();

	std::list<CShader*>::iterator ShaderPushBack(CShader* shader);

	void ShaderErase(std::list<CShader*>::iterator it);
private:

	//頂点レイアウトを作る関数
	void CreateInputLayout(ID3DBlob* blob, ID3D11InputLayout** inputLayout);
private:

	std::map<int, SShaderData>		m_shaderData;
	std::map<int, SShaderResource>	m_shaderResource;
	std::list<CShader*>				m_shaders;
};