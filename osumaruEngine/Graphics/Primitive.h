#pragma once
//プリミチィブクラス

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

	//コンストラクタ
	CPrimitive();

	//デストラクタ
	~CPrimitive();

	/*
	プリミティブを作成
	vertexBuffer	頂点バッファ
	vertexStride	頂点ストライド
	vertexNum		頂点数
	indexBuffer		インデックスバッファ
	indexNum		インデックス数
	formatIndex		インデックスバッファのフォーマット
	primitiveType	プリミティブの種類
	*/
	void Create(void* vertexBuffer, int vertexStride,int vertexNum, void* indexBuffer, int indexNum, EnFormatIndex formatIndex, EnPrimitiveType primitiveType);

	//頂点バッファを取得
	ID3D11Buffer* GetVertexBuffer() const
	{
		return m_vertexBuffer;
	}

	//インデックスバッファを取得
	ID3D11Buffer* GetIndexBuffer() const
	{
		return m_indexBuffer;
	}

	//頂点ストライドを取得
	int GetVertexStride()
	{
		return m_stride;
	}

	//インデックス数を取得
	int GetIndexNum()
	{
		return m_indexNum;
	}

	//プリミティブタイプを取得
	D3D11_PRIMITIVE_TOPOLOGY GetPrimitiveType()
	{
		return m_primitiveType;
	}

	//インデクスバッファのフォーマットを取得
	DXGI_FORMAT GetIndexFormat()
	{
		return m_indexFormat;
	}
private:
	ID3D11Buffer*					m_vertexBuffer = nullptr;									//頂点バッファ	
	ID3D11Buffer*					m_indexBuffer = nullptr;									//インデックスバッファ
	DXGI_FORMAT						m_indexFormat = DXGI_FORMAT_R16_UINT;						//インデックスバッファのフォーマット
	int								m_stride = 0;												//頂点バッファのストライド
	int								m_indexNum = 0;												//インデックス数
	D3D11_PRIMITIVE_TOPOLOGY		m_primitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;	//プリミティブタイプ
};