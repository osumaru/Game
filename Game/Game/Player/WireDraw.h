#pragma once

class CWireDraw : public Uncopyable
{
public:
	/*
	������
	startPos	�n�_�̍��W
	endPos		�I�_�̍��W
	color		�F
	*/
	void Init(const CVector3& startPos, const CVector3& endPos, const CVector3& color);

	void Update();

	//�`��
	void Draw();

	//�n�_��ݒ�
	void SetStartPosition(const CVector3& pos)
	{
		m_startPos = pos;
	}
	
	//�I�_��ݒ�
	void SetEndPosition(const CVector3& pos)
	{
		m_endPos = pos;
	}

	//�J���[��ݒ�
	void SetColor(const CVector3& color)
	{
		m_color = color;
	}

	struct SVSLayout
	{
		CVector4 pos;
		CVector3 color;
	};
private:
	CVector3 m_endPos;
	CVector3 m_startPos;
	CVector3 m_color;
	CPrimitive	m_primitive;
	CShader	m_ps;
	CShader m_vs;
	CConstantBuffer m_cb;
};