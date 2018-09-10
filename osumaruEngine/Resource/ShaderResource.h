#pragma once
#include "../Graphics/Shader.h"
struct SShaderResource
{
	ID3D11DeviceChild*				m_pShader;			//シェーダー
	ID3D11InputLayout*				m_pInputLayout;		//頂点レイアウト
	ID3DBlob*						m_blob;				//シェーダーデータ
};

struct SShaderData
{
	char* data;
	int filepos;
};

class CShaderResource : Uncopyable
{
public:
	SShaderData ReadFile(const char* filePath);

	/*
	エフェクトファイルを読み込む関数
	filepath		ファイルパス
	entryFuncName	関数の名前
	shaderType		シェーダーの種類
	*/
	SShaderResource Load(const char* filepath, const char* entryFuncName, CShader::EnShaderType shaderType);
private:

	//頂点レイアウトを作る関数
	void CreateInputLayout(ID3DBlob* blob, ID3D11InputLayout** inputLayout);

private:

	std::map<int, SShaderData>  m_shaderData;
	std::map<int, SShaderResource> m_shaders;
};