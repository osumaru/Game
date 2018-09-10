#pragma once
class CTexture;
//テクスチャのリソース管理クラス

class CTextureResource : Uncopyable
{
public:

	//テクスチャを取得
	CTexture* LoadTexture(const wchar_t* filePath);
private:
	std::map<int, std::unique_ptr<CTexture>> m_textures;	//テクスチャ
};