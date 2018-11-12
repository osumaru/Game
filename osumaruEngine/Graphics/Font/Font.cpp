#include "Font.h"

void CFont::Init(wchar_t* str)
{
	m_displayString = str;
	m_spriteBatch = std::make_unique<SpriteBatch>(GetDeviceContext());
	m_spriteFont = std::make_unique<SpriteFont>(GetDevice(), L"Assets/myfile.spritefont");
}

void CFont::Draw()
{
	//座標を画面中央を基点とする座標系から画面左上を基点とする座標系に変換
	CVector2 pos = m_position;
	pos.y = -pos.y;
	pos.x += FrameBufferWidth() / 2.0f;
	pos.y += FrameBufferHeight() / 2.0f;
	m_spriteBatch->Begin();
	m_color.x = 0.0f;
	m_color.y = 0.0f;
	m_color.z = 0.0f;
	m_spriteFont->DrawString(m_spriteBatch.get(), m_displayString, pos, m_color, 0.0f, g_XMZero, m_size);
	m_spriteBatch->End();

}