#include "Font.h"

void CFont::Init(wchar_t* str)
{
	m_displayString = str;
	m_spriteBatch = std::make_unique<SpriteBatch>(GetDeviceContext());
	m_spriteFont = std::make_unique<SpriteFont>(GetDevice(), L"Assets/myfile.spritefont");
}

void CFont::Draw()
{
	CVector2 pos = m_position;
	pos.y = -pos.y;
	pos.x += FrameBufferWidth() / 2.0f;
	pos.y += FrameBufferHeight() / 2.0f;
	m_spriteBatch->Begin();
	m_spriteFont->DrawString(m_spriteBatch.get(), m_displayString, pos);
	m_spriteBatch->End();

}