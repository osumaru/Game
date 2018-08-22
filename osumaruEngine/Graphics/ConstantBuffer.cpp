#include "engineStdafx.h"
#include "ConstantBuffer.h"


ConstantBuffer::ConstantBuffer() :
	m_buffer(nullptr)
{
}

ConstantBuffer::~ConstantBuffer()
{
	if (m_buffer != nullptr)
	{
		m_buffer->Release();
		m_buffer = nullptr;
	}

}

void ConstantBuffer::Create(int bufferSize, void* initData)
{
	D3D11_BUFFER_DESC desc;
	desc.ByteWidth = (((bufferSize - 1) / 16) + 1) * 16;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA resource;
	resource.pSysMem = initData;
	if (initData != nullptr)
	{
		GetDevice()->CreateBuffer(&desc, &resource, &m_buffer);
	}
	else
	{
		GetDevice()->CreateBuffer(&desc, nullptr, &m_buffer);
	}
}

void ConstantBuffer::Update(void* updateData)
{

	GetDeviceContext()->UpdateSubresource(m_buffer, 0, NULL, updateData, 0, 0);
}