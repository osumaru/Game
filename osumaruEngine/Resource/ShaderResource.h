#pragma once
//#include "../Graphics/Shader.h"
//struct SShaderResource
//{
//	ID3D11DeviceChild*				m_pShader;			//�V�F�[�_�[
//	ID3D11InputLayout*				m_pInputLayout;		//���_���C�A�E�g
//	ID3DBlob*						m_blob;				//�V�F�[�_�[�f�[�^
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
//�G�t�F�N�g�t�@�C����ǂݍ��ފ֐�
//filepath		�t�@�C���p�X
//entryFuncName	�֐��̖��O
//shaderType		�V�F�[�_�[�̎��
//*/
//	void Load(const char* filepath, const char* entryFuncName, EnShaderType shaderType);
//
//private:
//
//	std::map<int, SShaderData>  m_shaderData;
//	std::map<int, SShaderResource> m_shaders
//};