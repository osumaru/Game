#include "engineStdafx.h"
#include "TextureResource.h"



CTexture* CTextureResource::LoadTexture(const wchar_t* filePath)
{
	int hash = MakeHash(filePath);
	auto& map = m_textures.find(hash);
	if (map == m_textures.end())
	{
		std::unique_ptr<CTexture> texture;
		texture.reset(new CTexture);
		texture->Load(filePath);
		CTexture* tex = texture.get();
		m_textures.insert({ hash, std::move(texture) });
		return tex;
	}
	else
	{
		return map->second.get();
	}
}