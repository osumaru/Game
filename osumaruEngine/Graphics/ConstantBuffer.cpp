#include "engineStdafx.h"
#include "ConstantBuffer.h"


CConstantBuffer::CConstantBuffer() :
	m_buffer(nullptr)
{
}

CConstantBuffer::~CConstantBuffer()
{
}

void CConstantBuffer::Create(int bufferSize, const void* initData)
{
	D3D11_BUFFER_DESC desc;
	desc.ByteWidth = (((bufferSize - 1) / 16) + 1) * 16;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA resource;
	resource.pSysMem = initData;
	HRESULT hr;
	if (initData != nullptr)
	{
		hr = GetDevice()->CreateBuffer(&desc, &resource, m_buffer.GetAddressOf());
	}
	else
	{
		hr = GetDevice()->CreateBuffer(&desc, nullptr, m_buffer.GetAddressOf());
	}
	
}

void CConstantBuffer::Update(void* updateData)
{

	GetDeviceContext()->UpdateSubresource(m_buffer.Get(), 0, NULL, updateData, 0, 0);
}