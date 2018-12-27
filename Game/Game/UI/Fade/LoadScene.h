#pragma once
#include "../../Item/CEquipItem.h"
class CLoadScene: public IGameObject
{
public:
	CLoadScene();
	~CLoadScene();
	bool Start();
	void Update();
	void AfterDraw();
	void ColorUP();
	void ColorDown();
	void IsDraw(const bool setdraw)
	{
		m_isDraw = setdraw;
	}

	CEquipItem* GetEquipItemData()
	{
		return &m_equipItem;
	}
private:
	CFont			m_font[2];									//�t�H���g
	CVector2		m_fontNamePosition = { -350.0f,250.0f };	//���O�̏������W
	CVector2		m_fontTextPosition = { -450.0f,100.0f };	//�����̏������W
	CVector4		m_fontCol = CVector4::Black;				//�t�H���g�̃J���[
	int				m_number = 1;

	CSprite			m_LoadSprite[2];
	CTexture*		m_loadTexture[2];
	wchar_t			m_text[256];
	bool			m_isDraw = false;
	float			m_alpha = 1.0f;
	bool			m_isAlphaDown = true;

	bool			m_isTextChange = false;

	float			CHANGE_TIME = 5.0f;
	float			m_alphaTime = 1.0f;			//�Ó]�Ȃǂ��s������
	CEquipItem		m_equipItem;
};

