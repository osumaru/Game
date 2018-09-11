#pragma once
#include "../Graphics/Shader.h"
struct SShaderResource
{
	ID3D11DeviceChild*				m_pShader;			//�V�F�[�_�[
	ID3D11InputLayout*				m_pInputLayout;		//���_���C�A�E�g
	ID3DBlob*						m_blob;				//�V�F�[�_�[�f�[�^
	char*							entryFuncName;		//�֐���
	char*							fileName;			//�t�@�C����
	CShader::EnShaderType			shaderType;			//�V�F�[�_�[�̎��
};

struct SShaderData
{
	char*			data;		//�V�F�[�_�[�f�[�^
	int				filepos;	//�t�@�C���T�C�Y
	char*			fileName;	//�t�@�C����
};

class CShaderResource : Uncopyable
{
public:
	~CShaderResource();

	SShaderData ReadFile(const char* filePath);

	/*
	�G�t�F�N�g�t�@�C����ǂݍ��ފ֐�
	filepath		�t�@�C���p�X
	entryFuncName	�֐��̖��O
	shaderType		�V�F�[�_�[�̎��
	*/
	SShaderResource Load(const char* filepath, const char* entryFuncName, CShader::EnShaderType shaderType);

	//�V�F�[�_�[�t�@�C����S���ăR���p�C��
	void ReLoad();

	std::list<CShader*>::iterator ShaderPushBack(CShader* shader);

	void ShaderErase(std::list<CShader*>::iterator it);
private:

	//���_���C�A�E�g�����֐�
	void CreateInputLayout(ID3DBlob* blob, ID3D11InputLayout** inputLayout);
private:

	std::map<int, SShaderData>		m_shaderData;
	std::map<int, SShaderResource>	m_shaderResource;
	std::list<CShader*>				m_shaders;
};