#pragma once


class CFont : Uncopyable
{
public:
	/*
	‰Šú‰»ŠÖ”
	str	•\¦‚·‚é•¶š—ñ

	*/
	void Init(wchar_t* str);

	void SetPosition(CVector2 position)
	{
		m_position = position;
	}

	void SetString(wchar_t* str)
	{
		if (str == nullptr)
		{
			return;
		}
		m_displayString = str;
	}

	void Draw();
	
private:
	CVector2		m_position = CVector2::Zero;
	const wchar_t* m_displayString = nullptr;
	std::unique_ptr<SpriteFont>	m_spriteFont;
	std::unique_ptr<SpriteBatch> m_spriteBatch;
};