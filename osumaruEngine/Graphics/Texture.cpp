#include "engineStdafx.h"
#include "Texture.h"



CTexture::CTexture() :
	m_width(0),
	m_height(0),
	m_pTexture(nullptr),
	m_pShaderResource(nullptr)
{
}

CTexture::~CTexture()
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
	if (m_pShaderResource != nullptr)
	{
		m_pShaderResource->Release();
		m_pTexture = nullptr;
	}
}

void CTexture::Load(const wchar_t* filepath)
{
	CreateWICTextureFromFile(GetDevice(), filepath, &m_pTexture, &m_pShaderResource);
}

void CTexture::Create(int width, int height, EnTextureType textureType, DXGI_FORMAT format)
{
	m_width = width;
	m_height = height;
	UINT bindFlags = 0;
	switch (textureType)
	{
	case enRendertarget:
		bindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
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
	GetDevice()->CreateTexture2D(&tDesc, NULL, (ID3D11Texture2D**)&m_pTexture);
}