#include "engineStdafx.h"
#include "Shader.h"
#include "../Resource/ShaderResource.h"

CShader::CShader() :
	m_pShader(nullptr),
	m_pInputLayout(nullptr),
	m_blob(nullptr),
	m_filePath(nullptr),
	m_entryFuncName(nullptr),
	m_isErase(true)
{
	m_it = ShaderResource().ShaderPushBack(this);
}

CShader::~CShader()
{
	if (m_isErase)
	{
		ShaderResource().ShaderErase(m_it);
	}
}

void CShader::Load(const char* filepath, const char* entryFuncName, EnShaderType shaderType)
{
	m_filePath = filepath;
	m_entryFuncName = entryFuncName;
	m_shaderType = shaderType;
	SShaderResource shaderResource = ShaderResource().Load(filepath, entryFuncName, shaderType);
	m_blob = shaderResource.m_blob;
	m_pInputLayout = shaderResource.m_pInputLayout;
	m_pShader = shaderResource.m_pShader;
}

void CShader::ReLoad()
{
	if (m_entryFuncName == nullptr || m_filePath == nullptr)
	{
		return;
	}
	SShaderResource shaderResource = ShaderResource().Load(m_filePath, m_entryFuncName, m_shaderType);
	m_blob = shaderResource.m_blob;
	m_pInputLayout = shaderResource.m_pInputLayout;
	m_pShader = shaderResource.m_pShader;
}