#pragma once
//プリミチィブクラス

class Primitive
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

	Primitive();

	~Primitive();

	void Create(void* vertexBuffer, int vertexStride,int vertexNum, void* indexBuffer, int indexNum, EnFormatIndex formatIndex, EnPrimitiveType primitiveType);

	ID3D11Buffer* GetVertexBuffer()
	{
		return m_vertexBuffer;
	}

	ID3D11Buffer* GetIndexBuffer()
	{
		return m_indexBuffer;
	}
	int GetVertexStride()
	{
		return m_stride;
	}
	int GetIndexNum()
	{
		return m_indexNum;
	}

	D3D11_PRIMITIVE_TOPOLOGY GetPrimitiveType()
	{
		return m_primitiveType;
	}
	DXGI_FORMAT GetIndexFormat()
	{
		return m_indexFormat;
	}

private:
	ID3D11Buffer*					m_vertexBuffer;
	ID3D11Buffer*					m_indexBuffer;
	DXGI_FORMAT						m_indexFormat;
	int								m_stride;
	int								m_indexNum;
	D3D11_PRIMITIVE_TOPOLOGY		m_primitiveType;
};