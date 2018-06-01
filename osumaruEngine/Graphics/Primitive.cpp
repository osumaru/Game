#include "engineStdafx.h"
#include "Primitive.h"


Primitive::Primitive() :
	m_vertexBuffer(nullptr),
	m_indexBuffer(nullptr),
	m_indexFormat(DXGI_FORMAT_R16_UINT),
	m_indexNum(0),
	m_primitiveType(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP)
{
	
}

Primitive::~Primitive()
{
	if (m_vertexBuffer != nullptr)
	{
		//m_vertexBuffer->Release();
		m_vertexBuffer = nullptr;
	}
	if (m_indexBuffer != nullptr)
	{
		//m_indexBuffer->Release();
		m_indexBuffer != nullptr;
	}
}

void Primitive::Create(void* vertexBuffer, int vertexStride, int vertexNum, void* indexBuffer, int indexNum, EnFormatIndex formatIndex, EnPrimitiveType primitiveType)
{
	int size;
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
	m_indexNum = indexNum;
	D3D11_BUFFER_DESC bufferDesc;
	D3D11_SUBRESOURCE_DATA subresourceData;
	bufferDesc.ByteWidth = vertexStride * vertexNum;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.MiscFlags = 0;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.StructureByteStride = vertexStride;
	subresourceData.pSysMem = vertexBuffer;
	GetDevice()->CreateBuffer(&bufferDesc, &subresourceData, &m_vertexBuffer);
	D3D11_BUFFER_DESC bufferIndexDesc;
	D3D11_SUBRESOURCE_DATA subresourceIndexData;
	bufferIndexDesc.ByteWidth = m_indexNum * size;
	bufferIndexDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferIndexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferIndexDesc.MiscFlags = 0;
	bufferIndexDesc.CPUAccessFlags = 0;
	bufferIndexDesc.StructureByteStride = size;
	subresourceIndexData.pSysMem = indexBuffer;
	GetDevice()->CreateBuffer(&bufferIndexDesc, &subresourceIndexData, &m_indexBuffer);
	m_stride = vertexStride;
}