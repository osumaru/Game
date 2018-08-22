#pragma once
//�萔�o�b�t�@�N���X

class ConstantBuffer
{
public:
	//�R���X�g���N�^
	ConstantBuffer();

	//�f�X�g���N�^
	~ConstantBuffer();

	/*
	�萔�o�b�t�@���쐬
	bufferSize	�o�b�t�@�̃X�g���C�Y(�T�C�Y)
	initData	�������p�̃f�[�^
	*/
	void Create(int bufferSize, void* initData);

	/*
	���\�[�X�̍X�V
	updateData	�X�V�p�̃f�[�^
	*/
	void Update(void* updateData);

	//�o�b�t�@���擾
	ID3D11Buffer* GetBody()
	{
		return m_buffer;
	}
private:
	ID3D11Buffer*					m_buffer;//�o�b�t�@
};

