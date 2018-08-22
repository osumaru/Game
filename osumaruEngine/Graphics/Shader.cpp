#include "engineStdafx.h"
#include "Shader.h"

Shader::Shader() :
	m_pShaderData(nullptr),
	m_pShader(nullptr),
	m_pInputLayout(nullptr),
	m_blob(nullptr)
{
	
}

Shader::~Shader()
{
	if (m_pShader != nullptr)
	{
		m_pShader->Release();
		m_pShader = nullptr;
	}
	if (m_pInputLayout != nullptr)
	{
		m_pInputLayout->Release();
		m_pInputLayout = nullptr;
	}
	if (m_blob != nullptr)
	{
		m_blob->Release();
		m_blob = nullptr;
	}
}

void Shader::Load(const char* filepath, const char* entryFuncName, EnShaderType shaderType)
{
	FILE* file;
	file = fopen(filepath, "rb");
	fseek(file, 0, SEEK_END);
	fpos_t filepos;
	fgetpos(file, &filepos);
	fseek(file, 0, SEEK_SET);
	m_pShaderData.reset(new char[filepos]);
	fread(m_pShaderData.get(), filepos, 1, file);
	DWORD shaderCompilerOption = 0;
	shaderCompilerOption |= D3DCOMPILE_ENABLE_STRICTNESS;
	shaderCompilerOption |= D3DCOMPILE_OPTIMIZATION_LEVEL3;
	ID3DBlob* errorBlob;
	char* shaderTypeName[] = 
	{
		"vs_5_0",
		"ps_5_0",
		"cs_5_0"
	};
	HRESULT hr = D3DCompile(m_pShaderData.get(), (int)filepos, nullptr,
		nullptr, nullptr, entryFuncName, shaderTypeName[shaderType], shaderCompilerOption, 0, &m_blob, &errorBlob);
	if (FAILED(hr))
	{
		if (errorBlob != nullptr)
		{
			static char errorMessage[10240];
			sprintf(errorMessage, "filePath : %s, %s", filepath, (char*)errorBlob->GetBufferPointer());
			MessageBox(NULL, errorMessage, "シェーダーコンパイルエラー", MB_OK);
			return;
		}
	}
	switch (shaderType)
	{
	case enVS:
		GetDevice()->CreateVertexShader(m_blob->GetBufferPointer(), m_blob->GetBufferSize(), NULL, (ID3D11VertexShader**)&m_pShader);
		CreateInputLayout(m_blob);
		break;
	case enPS:
		GetDevice()->CreatePixelShader(m_blob->GetBufferPointer(), m_blob->GetBufferSize(), NULL, (ID3D11PixelShader**)&m_pShader);
		break;
	case enCS:
		break;
	}

}

void Shader::CreateInputLayout(ID3DBlob* blob)
{
	ID3D11ShaderReflection* shaderReflection;
	D3DReflect(blob->GetBufferPointer(), blob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&shaderReflection);
	D3D11_SHADER_DESC desc;
	shaderReflection->GetDesc(&desc);
	std::vector<D3D11_INPUT_ELEMENT_DESC> descVector;
	for (int i = 0;i < desc.InputParameters;i++)
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

	GetDevice()->CreateInputLayout(&descVector[0], descVector.size(), blob->GetBufferPointer(), blob->GetBufferSize(), &m_pInputLayout);

}