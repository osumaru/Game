#pragma once
//#include "../Graphics/Shader.h"
//struct SShaderResource
//{
//	ID3D11DeviceChild*				m_pShader;			//シェーダー
//	ID3D11InputLayout*				m_pInputLayout;		//頂点レイアウト
//	ID3DBlob*						m_blob;				//シェーダーデータ
//};
//
//struct SShaderData
//{
//	char* data;
//	int filepos;
//};
//
//class CShaderResource : Uncopyable
//{
//
//
//public:
//	SShaderData* ReadFile(char* filePath);
//
//	/*
//エフェクトファイルを読み込む関数
//filepath		ファイルパス
//entryFuncName	関数の名前
//shaderType		シェーダーの種類
//*/
//	void Load(const char* filepath, const char* entryFuncName, EnShaderType shaderType);
//
//private:
//
//	std::map<int, SShaderData>  m_shaderData;
//	std::map<int, SShaderResource> m_shaders
//};