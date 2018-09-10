#include "engineStdafx.h"
#include "ShaderResource.h"
//
//SShaderData CShaderResource::ReadFile(char* filePath)
//{
//	int hash = MakeHash(filePath);
//	auto& map = m_shaderData.find(hash);
//	if (map == m_shaderData.end())
//	{
//		char* data;
//		//シェーダーファイルを開いて読み込む
//		FILE* file;
//		file = fopen(filePath, "rb");
//		fseek(file, 0, SEEK_END);
//		fpos_t filepos;
//		fgetpos(file, &filepos);
//		fseek(file, 0, SEEK_SET);
//		data = new char[filepos];
//		SShaderData ret;
//		ret.data = data;
//		ret.filepos = filepos;
//		m_shaderData.insert({ hash, ret });
//		return ret;
//	}
//	else
//	{
//		return map->second;
//	}
//}
//
//void CShaderResource::Load(const char * filepath, const char * entryFuncName, EnShaderType shaderType)
//{
//	DWORD shaderCompilerOption = 0;
//	shaderCompilerOption |= D3DCOMPILE_ENABLE_STRICTNESS;
//	shaderCompilerOption |= D3DCOMPILE_OPTIMIZATION_LEVEL3;
//	ID3DBlob* errorBlob;
//	char* shaderTypeName[] =
//	{
//		"vs_5_0",
//		"ps_5_0",
//		"cs_5_0"
//	};
//
//	//HRESULT hr = D3DCompile(m_pShaderData.get(), (int)filepos, nullptr,
//	//	nullptr, nullptr, entryFuncName, shaderTypeName[shaderType], shaderCompilerOption, 0, &m_blob, &errorBlob);
//
//	//if (FAILED(hr))
//	//{
//	//	if (errorBlob != nullptr)
//	//	{
//	//		//エラーを吐き出していた場合それを表示して呼び出し元へ戻る
//	//		static char errorMessage[10240];
//	//		sprintf(errorMessage, "filePath : %s, %s", filepath, (char*)errorBlob->GetBufferPointer());
//	//		MessageBox(NULL, errorMessage, "シェーダーコンパイルエラー", MB_OK);
//	//		return;
//	//	}
//	//}
//	//switch (shaderType)
//	//{
//	//case enVS:
//	//	GetDevice()->CreateVertexShader(m_blob->GetBufferPointer(), m_blob->GetBufferSize(), NULL, (ID3D11VertexShader**)&m_pShader);
//	//	CreateInputLayout(m_blob);
//	//	break;
//	//case enPS:
//	//	GetDevice()->CreatePixelShader(m_blob->GetBufferPointer(), m_blob->GetBufferSize(), NULL, (ID3D11PixelShader**)&m_pShader);
//	//	break;
//	//case enCS:
//	//	break;
//	//}
//}
