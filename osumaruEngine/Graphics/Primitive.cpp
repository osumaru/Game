#include "engineStdafx.h"
#include "Primitive.h"


CPrimitive::CPrimitive() :
	m_vertexBuffer(nullptr),
	m_indexBuffer(nullptr),
	m_indexFormat(DXGI_FORMAT_R16_UINT),
	m_indexNum(0),
	m_primitiveType(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP)
{
	
}

CPrimitive::~CPrimitive()
{
}


void CPrimitive::Create(void* vertexBuffer, int vertexStride, int vertexNum, void* indexBuffer, int indexNum, EnFormatIndex formatIndex, EnPrimitiveType primitiveType)
{
	int size;
	//インデックスバッファのフォーマットを決める
	switch (formatIndex)
	{
	case enIndex16:
		m_indexFormat = DXGI_FORMAT_R16_UINT;
		size = sizeof(WORD);
		break;

	case enIndex32:
		m_indexFormat = DXGI_FORMAT_R32_UINT;
		size = sizeof(DWORD);
		break;
	}
	//プリミティブの種類を決める
	switch (primitiveType)
	{
	case enTypeLineList:
		m_primitiveType = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
		break;
	case enTypeTriangleList:
		m_primitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		break;
	case enTypeTriangleStrip:
		m_primitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
		break;
	}
	//頂点バッファを作る
	m_indexNum = indexNum;
	m_vertexNum = vertexNum;
	D3D11_BUFFER_DESC bufferDesc;
	D3D11_SUBRESOURCE_DATA subresourceData;
	bufferDesc.ByteWidth = vertexStride * vertexNum;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.MiscFlags = 0;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.StructureByteStride = vertexStride;
	subresourceData.pSysMem = vertexBuffer;
	HRESULT hr = GetDevice()->CreateBuffer(&bufferDesc, &subresourceData, m_vertexBuffer.GetAddressOf());

	//インデックスバッファを作る
	D3D11_BUFFER_DESC bufferIndexDesc;
	D3D11_SUBRESOURCE_DATA subresourceIndexData;
	bufferIndexDesc.ByteWidth = m_indexNum * size;
	bufferIndexDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferIndexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferIndexDesc.MiscFlags = 0;
	bufferIndexDesc.CPUAccessFlags = 0;
	bufferIndexDesc.StructureByteStride = size;
	subresourceIndexData.pSysMem = indexBuffer;
	hr = GetDevice()->CreateBuffer(&bufferIndexDesc, &subresourceIndexData, m_indexBuffer.GetAddressOf());
	m_stride = vertexStride;
}

void CPrimitive::Update(void* vertexBuffer, void* indexBuffer)
{
	Engine().GetDeviceContext()->UpdateSubresource(m_vertexBuffer.Get(), 0, NULL, vertexBuffer, 0, 0);
	Engine().GetDeviceContext()->UpdateSubresource(m_indexBuffer.Get(), 0, NULL, indexBuffer, 0, 0);
	
}