#include "Font.h"

void CFont::Init(wchar_t* str)
{
	SetString(str);
	m_spriteFont = std::make_unique<SpriteFont>(GetDevice(), L"Assets/myfile.spritefont");
}

void CFont::Draw()
{
	//座標を画面中央を基点とする座標系から画面左上を基点とする座標系に変換
	CVector2 pos = m_position;
	pos.y = -pos.y;
	pos.x += FrameBufferWidth() / 2.0f;
	pos.y += FrameBufferHeight() / 2.0f;
	Engine().GetSpriteBatch()->Begin();
	m_spriteFont->DrawString(Engine().GetSpriteBatch(), m_displayString.get(), pos, m_color, 0.0f, g_XMZero, m_size);
	Engine().GetSpriteBatch()->End();
}