#include "engineStdafx.h"
#include "Texture.h"



CTexture::CTexture() :
	m_width(0),
	m_height(0),
	m_pTexture(nullptr),
	m_pUnorderedAccess(nullptr),
	m_pShaderResource(nullptr)
{
}

CTexture::~CTexture()
{
}

void CTexture::Load(const wchar_t* filepath)
{
	HRESULT hr;
	hr = CreateWICTextureFromFile(GetDevice(), filepath, m_pTexture.GetAddressOf(), m_pShaderResource.GetAddressOf());
}

void CTexture::Create(int width, int height, EnTextureType textureType, DXGI_FORMAT format)
{

	m_width = width;
	m_height = height;
	UINT bindFlags = 0;
	switch (textureType)
	{
	case enRendertarget:
		bindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
		break;
	case enDepthStencil:
		bindFlags = D3D11_BIND_DEPTH_STENCIL;
		break;
	}
	D3D11_TEXTURE2D_DESC tDesc;
	ZeroMemory(&tDesc, sizeof(tDesc));

	tDesc.Width = m_width;
	tDesc.Height = m_height;
	tDesc.Format = format;
	tDesc.MiscFlags = 0;
	tDesc.ArraySize = 1;
	tDesc.BindFlags = bindFlags;
	tDesc.CPUAccessFlags = 0;
	tDesc.MipLevels = 0;
	tDesc.SampleDesc.Count = 1;
	tDesc.SampleDesc.Quality = 0;
	tDesc.Usage = D3D11_USAGE_DEFAULT;
	HRESULT hr = GetDevice()->CreateTexture2D(&tDesc, NULL, m_pTexture2D.GetAddressOf() );
	hr = GetDevice()->CreateShaderResourceView(m_pTexture2D.Get(), nullptr, m_pShaderResource.GetAddressOf());
	hr = GetDevice()->CreateUnorderedAccessView(m_pTexture2D.Get(), nullptr, m_pUnorderedAccess.GetAddressOf());
}