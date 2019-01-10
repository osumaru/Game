#pragma once
//�������`�悷��N���X

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
	�������֐�
	str	�\�����镶����
	*/
	void Init(wchar_t* str);

	/*
	���W��ݒ肷��֐�
	��ʂ̒�����(0.0f, 0.0f)�Ƃ������(-1.0f, 1.0f),�E����(1.0f, -1.0f)�Ƃ���
	*/
	void SetPosition(CVector2 position)
	{
		m_position = position;
	}
	/*
	�\���p�̕������ݒ�
	*/
	void SetString(const wchar_t* str)
	{
		if (str == nullptr)
		{
			return;
		}
		//�k����������+1
		m_displayString = std::make_unique<wchar_t[]>(wcslen(str) + 1);
		wcscpy(m_displayString.get(), str);
	}

	//�T�C�Y��ݒ�
	void SetSize(const CVector2& size)
	{
		m_size = size;
	}

	//�F��ݒ�
	void SetColor(const CVector4& color)
	{
		m_color = color;
	}

	//�`��֐�
	void Draw();
	
private:
	CVector2		m_size = CVector2::One;				//�T�C�Y
	CVector4		m_color = CVector4::Black;			//�J���[
	CVector2		m_position = CVector2::Zero;		//���W
	std::unique_ptr<wchar_t[]> m_displayString;			//�\���p�̕�����
	std::unique_ptr<SpriteFont>	m_spriteFont;
};