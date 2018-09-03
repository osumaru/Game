#pragma once
//�v���~�`�B�u�N���X

class CPrimitive
{
public:
	enum EnFormatIndex
	{
		enIndex16,
		enIndex32,
	};

	enum EnPrimitiveType
	{
		enTypeLineList,
		enTypeTriangleStrip,
		enTypeTriangleList,
	};

	//�R���X�g���N�^
	CPrimitive();

	//�f�X�g���N�^
	~CPrimitive();

	/*
	�v���~�e�B�u���쐬
	vertexBuffer	���_�o�b�t�@
	vertexStride	���_�X�g���C�h
	vertexNum		���_��
	indexBuffer		�C���f�b�N�X�o�b�t�@
	indexNum		�C���f�b�N�X��
	formatIndex		�C���f�b�N�X�o�b�t�@�̃t�H�[�}�b�g
	primitiveType	�v���~�e�B�u�̎��
	*/
	void Create(void* vertexBuffer, int vertexStride,int vertexNum, void* indexBuffer, int indexNum, EnFormatIndex formatIndex, EnPrimitiveType primitiveType);

	//���_�o�b�t�@���擾
	ID3D11Buffer* GetVertexBuffer() const
	{
		return m_vertexBuffer;
	}

	//�C���f�b�N�X�o�b�t�@���擾
	ID3D11Buffer* GetIndexBuffer() const
	{
		return m_indexBuffer;
	}

	//���_�X�g���C�h���擾
	int GetVertexStride()
	{
		return m_stride;
	}

	//�C���f�b�N�X�����擾
	int GetIndexNum()
	{
		return m_indexNum;
	}

	//�v���~�e�B�u�^�C�v���擾
	D3D11_PRIMITIVE_TOPOLOGY GetPrimitiveType()
	{
		return m_primitiveType;
	}

	//�C���f�N�X�o�b�t�@�̃t�H�[�}�b�g���擾
	DXGI_FORMAT GetIndexFormat()
	{
		return m_indexFormat;
	}
private:
	ID3D11Buffer*					m_vertexBuffer = nullptr;									//���_�o�b�t�@	
	ID3D11Buffer*					m_indexBuffer = nullptr;									//�C���f�b�N�X�o�b�t�@
	DXGI_FORMAT						m_indexFormat = DXGI_FORMAT_R16_UINT;						//�C���f�b�N�X�o�b�t�@�̃t�H�[�}�b�g
	int								m_stride = 0;												//���_�o�b�t�@�̃X�g���C�h
	int								m_indexNum = 0;												//�C���f�b�N�X��
	D3D11_PRIMITIVE_TOPOLOGY		m_primitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;	//�v���~�e�B�u�^�C�v
};