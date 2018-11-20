#pragma once
#include "../Graphics/Shader.h"

struct SShaderResource
{
	Microsoft::WRL::ComPtr<ID3D11DeviceChild>		m_pShader;			//�V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11InputLayout>		m_pInputLayout;		//���_���C�A�E�g
	Microsoft::WRL::ComPtr<ID3DBlob>				m_blob;				//�V�F�[�_�[�̃o�b�t�@
	char*											entryFuncName;		//�֐���(�����[�h���Ɏg��)
	char*											fileName;			//�t�@�C����(�����[�h���Ɏg��)
	CShader::EnShaderType							shaderType;			//�V�F�[�_�[�̎��(�����[�h���Ɏg��)
};

struct SShaderData
{
	char*			data;		//�V�F�[�_�[�f�[�^
	int				filepos;	//�t�@�C���T�C�Y
	char*			fileName;	//�t�@�C����(�����[�h���Ɏg��)
};

//�V�F�[�_�[���\�[�X���Ǘ�����N���X
class CShaderResource : Uncopyable
{
public:
	//�f�X�g���N�^
	~CShaderResource();

	/*
	filePath	�t�@�C���p�X
	ret�@�V�F�[�_�[�̃t�@�C����ǂݍ��񂾃f�[�^
	*/
	SShaderData ReadFile(const char* filePath);

	/*
	�G�t�F�N�g�t�@�C����ǂݍ��ފ֐�
	filepath		�t�@�C���p�X
	entryFuncName	�֐��̖��O
	shaderType		�V�F�[�_�[�̎��
	ret				�V�F�[�_�[�̃o�b�t�@�A�V�F�[�_�[�A���_���C�A�E�g
	*/
	SShaderResource Load(const char* filepath, const char* entryFuncName, CShader::EnShaderType shaderType);

	//�V�F�[�_�[�t�@�C����S���ăR���p�C��
	void ReLoad();

	//�����[�h����V�F�[�_�[���X�g�ɓo�^
	std::list<CShader*>::iterator ShaderPushBack(CShader* shader);

	//�����[�h����V�F�[�_�[���X�g����폜
	void ShaderErase(std::list<CShader*>::iterator it);
private:

	//���_���C�A�E�g�����֐�
	void CreateInputLayout(Microsoft::WRL::ComPtr<ID3DBlob> blob, ID3D11InputLayout** inputLayout);
private:

	std::map<int, SShaderData>		m_shaderData;			//�V�F�[�_�[�̃f�[�^
	std::map<int, SShaderResource>	m_shaderResource;		//�V�F�[�_�[��
	std::list<CShader*>				m_shaders;				//�����[�h�p�̃V�F�[�_�[���X�g
};