#pragma once
//�萔�o�b�t�@�N���X

class CConstantBuffer
{
public:
	//�R���X�g���N�^
	CConstantBuffer();

	//�f�X�g���N�^
	~CConstantBuffer();

	/*
	�萔�o�b�t�@���쐬
	bufferSize	�o�b�t�@�̃X�g���C�Y(�T�C�Y)
	initData	�������p�̃f�[�^
	*/
	void Create(int bufferSize, const void* initData);

	/*
	���\�[�X�̍X�V
	updateData	�X�V�p�̃f�[�^
	*/
	void Update(void* updateData);

	//�o�b�t�@���擾
	Microsoft::WRL::ComPtr<ID3D11Buffer>& GetBody()
	{
		return m_buffer;
	}

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_buffer;//�o�b�t�@
};

