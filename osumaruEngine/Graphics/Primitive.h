#pragma once
//�v���~�`�B�u�N���X

class CPrimitive : Uncopyable
{
public:
	//�C���f�b�N�X�o�b�t�@�̎��
	enum EnFormatIndex
	{
		enIndex16,
		enIndex32,
	};

	//�v���~�e�B�u�̎��
	enum EnPrimitiveType
	{	
		enTypeLineList,			//���C�����X�g
		enTypeTriangleStrip,	//�g���C�A���O���X�g���b�v
		enTypeTriangleList,		//�g���C�A���O�����X�g
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

	void Update(void* vertexBuffer, void* indexBuffer);

	//���_�o�b�t�@���擾
	Microsoft::WRL::ComPtr<ID3D11Buffer>& GetVertexBuffer()
	{
		return m_vertexBuffer;
	}

	//�C���f�b�N�X�o�b�t�@���擾
	Microsoft::WRL::ComPtr<ID3D11Buffer>& GetIndexBuffer()
	{
		return m_indexBuffer;
	}

	//���_�X�g���C�h���擾
	int GetVertexStride() const
	{
		return m_stride;
	}

	//�C���f�b�N�X�����擾
	int GetIndexNum() const
	{
		return m_indexNum;
	}

	//�v���~�e�B�u�^�C�v���擾
	D3D11_PRIMITIVE_TOPOLOGY GetPrimitiveType() const
	{
		return m_primitiveType;
	}

	//�C���f�N�X�o�b�t�@�̃t�H�[�}�b�g���擾
	DXGI_FORMAT GetIndexFormat() const
	{
		return m_indexFormat;
	}
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer>			m_vertexBuffer = nullptr;									//���_�o�b�t�@	
	Microsoft::WRL::ComPtr<ID3D11Buffer>			m_indexBuffer = nullptr;									//�C���f�b�N�X�o�b�t�@
	DXGI_FORMAT										m_indexFormat = DXGI_FORMAT_R16_UINT;						//�C���f�b�N�X�o�b�t�@�̃t�H�[�}�b�g
	int												m_stride = 0;												//���_�o�b�t�@�̃X�g���C�h
	int												m_indexNum = 0;												//�C���f�b�N�X��
	int												m_vertexNum = 0;
	int												m_vertexStride = 0;
	D3D11_PRIMITIVE_TOPOLOGY						m_primitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;	//�v���~�e�B�u�^�C�v
};