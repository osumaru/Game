#pragma once
//文字列を描画するクラス

class CFont : Uncopyable
{
public:
	CFont()
	{

	}

	~CFont()
	{

	}

	/*
	初期化関数
	str	表示する文字列
	*/
	void Init(wchar_t* str);

	/*
	座標を設定する関数
	画面の中央を(0.0f, 0.0f)とし左上を(-1.0f, 1.0f),右下を(1.0f, -1.0f)とする
	*/
	void SetPosition(CVector2 position)
	{
		m_position = position;
	}
	/*
	表示用の文字列を設定
	*/
	void SetString(const wchar_t* str)
	{
		if (str == nullptr)
		{
			return;
		}
		//ヌル文字分で+1
		m_displayString = std::make_unique<wchar_t[]>(wcslen(str) + 1);
		wcscpy(m_displayString.get(), str);
	}

	//サイズを設定
	void SetSize(const CVector2& size)
	{
		m_size = size;
	}

	//色を設定
	void SetColor(const CVector4& color)
	{
		m_color = color;
	}

	//描画関数
	void Draw();
	
private:
	CVector2		m_size = CVector2::One;				//サイズ
	CVector4		m_color = CVector4::Black;			//カラー
	CVector2		m_position = CVector2::Zero;		//座標
	std::unique_ptr<wchar_t[]> m_displayString;			//表示用の文字列
	std::unique_ptr<SpriteFont>	m_spriteFont;
};