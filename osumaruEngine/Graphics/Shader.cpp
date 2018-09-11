#include "engineStdafx.h"
#include "Shader.h"
#include "../Resource/ShaderResource.h"

CShader::CShader() :
	m_pShader(nullptr),
	m_pInputLayout(nullptr),
	m_blob(nullptr)
{
	
}

CShader::~CShader()
{
}

void CShader::Load(const char* filepath, const char* entryFuncName, EnShaderType shaderType)
{
	SShaderResource shaderResource = ShaderResource().Load(filepath, entryFuncName, shaderType);
	m_blob = shaderResource.m_blob;
	m_pInputLayout = shaderResource.m_pInputLayout;
	m_pShader = shaderResource.m_pShader;
}