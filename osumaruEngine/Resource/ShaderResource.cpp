#include "engineStdafx.h"
#include "ShaderResource.h"

CShaderResource::~CShaderResource()
{
	while (!m_shaders.empty())
	{
		CShader* shader = m_shaders.back();
		shader->EraseFlgFold();
		m_shaders.pop_back();
	}
}

SShaderData CShaderResource::ReadFile(const char* filePath)
{
	int hash = MakeHash(filePath);
	auto& map = m_shaderData.find(hash);
	if (map == m_shaderData.end())
	{
		char* data;
		//シェーダーファイルを開いて読み込む
		FILE* file;
		file = fopen(filePath, "rb");
		fseek(file, 0, SEEK_END);
		fpos_t filepos;
		fgetpos(file, &filepos);
		fseek(file, 0, SEEK_SET);
		data = new char[filepos];
		fread(data, filepos, 1, file);
		SShaderData ret;
		ret.data = data;
		ret.filepos = filepos;
		ret.fileName = new char[strlen(filePath)];
		strcpy(ret.fileName, filePath);
		m_shaderData.insert({ hash, ret });
		return ret;
	}
	else
	{
		return map->second;
	}
}

SShaderResource CShaderResource::Load(const char* filepath, const char* entryFuncName, CShader::EnShaderType shaderType)
{

	char hashName[100];
	strcpy(hashName, filepath);
	strcat(hashName, entryFuncName);

	int hash = MakeHash(hashName);
	auto& map = m_shaderResource.find(hash);
	if (map == m_shaderResource.end())
	{
		SShaderData shaderData = ReadFile(filepath);

		DWORD shaderCompilerOption = 0;
		shaderCompilerOption |= D3DCOMPILE_ENABLE_STRICTNESS;
		shaderCompilerOption |= D3DCOMPILE_OPTIMIZATION_LEVEL3;
		char* shaderTypeName[] =
		{
			"vs_5_0",
			"ps_5_0",
			"cs_5_0"
		};
		SShaderResource shaderResource;
		shaderResource.m_blob = nullptr;
		shaderResource.m_pInputLayout = nullptr;
		shaderResource.m_pShader = nullptr;
		ID3DBlob* errorBlob;
		HRESULT hr = D3DCompile(shaderData.data, shaderData.filepos, nullptr,
			nullptr, nullptr, entryFuncName, shaderTypeName[shaderType], shaderCompilerOption, 0, &shaderResource.m_blob, &errorBlob);

		if (FAILED(hr))
		{
			if (errorBlob != nullptr)
			{
				//エラーを吐き出していた場合それを表示して呼び出し元へ戻る
				static char errorMessage[10240];
				sprintf(errorMessage, "filePath : %s, %s", filepath, (char*)errorBlob->GetBufferPointer());
				MessageBox(NULL, errorMessage, "シェーダーコンパイルエラー", MB_OK);
				return shaderResource;
			}
		}
		switch (shaderType)
		{
		case CShader::enVS:
			GetDevice()->CreateVertexShader(shaderResource.m_blob->GetBufferPointer(), shaderResource.m_blob->GetBufferSize(), NULL, (ID3D11VertexShader**)&shaderResource.m_pShader);
			CreateInputLayout(shaderResource.m_blob, &shaderResource.m_pInputLayout);
			break;
		case CShader::enPS:
			GetDevice()->CreatePixelShader(shaderResource.m_blob->GetBufferPointer(), shaderResource.m_blob->GetBufferSize(), NULL, (ID3D11PixelShader**)&shaderResource.m_pShader);
			break;
		case CShader::enCS:
			break;
		}
		shaderResource.entryFuncName = new char[strlen(entryFuncName)];
		strcpy(shaderResource.entryFuncName, entryFuncName);
		shaderResource.fileName= new char[strlen(filepath)];
		strcpy(shaderResource.fileName, filepath);
		shaderResource.shaderType = shaderType;
		m_shaderResource.insert({ hash, shaderResource });
		return shaderResource;
	}
	else
	{
		return map->second;
	}
}

void CShaderResource::ReLoad()
{
	for (auto& map : m_shaderData)
	{
		char* data;
		//シェーダーファイルを開いて読み込む
		FILE* file;
		file = fopen(map.second.fileName, "rb");
		fseek(file, 0, SEEK_END);
		fpos_t filepos;
		fgetpos(file, &filepos);
		fseek(file, 0, SEEK_SET);
		data = new char[filepos];
		fread(data, filepos, 1, file);
		delete[] map.second.data;
		map.second.data = data;
		map.second.filepos = filepos;
	}
	for (auto& map : m_shaderResource)
	{
		int hash = MakeHash(map.second.fileName);
		SShaderData shaderData = m_shaderData.find(hash)->second;

		DWORD shaderCompilerOption = 0;
		shaderCompilerOption |= D3DCOMPILE_ENABLE_STRICTNESS;
		shaderCompilerOption |= D3DCOMPILE_OPTIMIZATION_LEVEL3;
		char* shaderTypeName[] =
		{
			"vs_5_0",
			"ps_5_0",
			"cs_5_0"
		};
		if (map.second.m_blob != nullptr)
		{
			map.second.m_blob->Release();
			map.second.m_blob = nullptr;
		}
		if (map.second.m_pInputLayout != nullptr)
		{
			map.second.m_pInputLayout->Release();
			map.second.m_pInputLayout = nullptr;
		}
		if (map.second.m_pShader != nullptr)
		{
			map.second.m_pShader->Release();
			map.second.m_pShader = nullptr;
		}
		ID3DBlob* errorBlob;
		HRESULT hr = D3DCompile(shaderData.data, shaderData.filepos, nullptr,
			nullptr, nullptr, map.second.entryFuncName, shaderTypeName[map.second.shaderType], shaderCompilerOption, 0, &map.second.m_blob, &errorBlob);

		if (FAILED(hr))
		{
			if (errorBlob != nullptr)
			{
				//エラーを吐き出していた場合それを表示して呼び出し元へ戻る
				static char errorMessage[10240];
				sprintf(errorMessage, "filePath : %s, %s", map.second.fileName, (char*)errorBlob->GetBufferPointer());
				MessageBox(NULL, errorMessage, "シェーダーコンパイルエラー", MB_OK);
			}
		}
		switch (map.second.shaderType)
		{
		case CShader::enVS:
			GetDevice()->CreateVertexShader(map.second.m_blob->GetBufferPointer(), map.second.m_blob->GetBufferSize(), NULL, (ID3D11VertexShader**)&map.second.m_pShader);
			CreateInputLayout(map.second.m_blob, &map.second.m_pInputLayout);
			break;
		case CShader::enPS:
			GetDevice()->CreatePixelShader(map.second.m_blob->GetBufferPointer(), map.second.m_blob->GetBufferSize(), NULL, (ID3D11PixelShader**)&map.second.m_pShader);
			break;
		case CShader::enCS:
			break;
		}
	}

	for (auto& shader : m_shaders)
	{
		shader->ReLoad();
	}
}

void CShaderResource::CreateInputLayout(ID3DBlob * blob, ID3D11InputLayout** inputLayout)
{
	//頂点シェーダーのデータから頂点レイアウトの情報を読み込む
	ID3D11ShaderReflection* shaderReflection;
	D3DReflect(blob->GetBufferPointer(), blob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&shaderReflection);
	D3D11_SHADER_DESC desc;
	shaderReflection->GetDesc(&desc);
	std::vector<D3D11_INPUT_ELEMENT_DESC> descVector;
	//頂点レイアウトを作成
	for (int i = 0; i < desc.InputParameters; i++)
	{
		D3D11_SIGNATURE_PARAMETER_DESC signatureDesc;
		shaderReflection->GetInputParameterDesc(i, &signatureDesc);
		D3D11_INPUT_ELEMENT_DESC desc;
		desc.InputSlot = 0;
		desc.SemanticIndex = signatureDesc.SemanticIndex;
		desc.SemanticName = signatureDesc.SemanticName;
		desc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		desc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		desc.InstanceDataStepRate = 0;
		if (signatureDesc.Mask == 1)
		{
			if (signatureDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
			{
				desc.Format = DXGI_FORMAT_R32_FLOAT;
			}
			else if (signatureDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
			{
				desc.Format = DXGI_FORMAT_R32_SINT;
			}
			else if (signatureDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
			{
				desc.Format = DXGI_FORMAT_R32_UINT;
			}
		}
		else if (signatureDesc.Mask <= 3)
		{
			if (signatureDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
			{
				desc.Format = DXGI_FORMAT_R32G32_FLOAT;
			}
			else if (signatureDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
			{
				desc.Format = DXGI_FORMAT_R32G32_SINT;
			}
			else if (signatureDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
			{
				desc.Format = DXGI_FORMAT_R32G32_UINT;
			}
		}
		else if (signatureDesc.Mask <= 7)
		{
			if (signatureDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
			{
				desc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
			}
			else if (signatureDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
			{
				desc.Format = DXGI_FORMAT_R32G32B32_SINT;
			}
			else if (signatureDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
			{
				desc.Format = DXGI_FORMAT_R32G32B32_UINT;
			}
		}
		else if (signatureDesc.Mask <= 15)
		{
			if (signatureDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
			{
				desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			}
			else if (signatureDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
			{
				desc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
			}
			else if (signatureDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
			{
				desc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
			}
		}
		descVector.push_back(desc);
	}
	GetDevice()->CreateInputLayout(&descVector[0], descVector.size(), blob->GetBufferPointer(), blob->GetBufferSize(), inputLayout);
}

std::list<CShader*>::iterator CShaderResource::ShaderPushBack(CShader* shader)
{
	m_shaders.push_back(shader);
	std::list<CShader*>::iterator it = m_shaders.end();
	it--;
	return it;
}

void CShaderResource::ShaderErase(std::list<CShader*>::iterator it)
{
	m_shaders.erase(it);
}