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

	//���_�o�b�t�@
	struct SVSLayout
	{
		CVector4 pos;
		CVector3 color;
	};
private:
	static const int VERTEX_NUM = 2;
	CVector3		m_startPos;		//�n�_�̍��W
	CVector3		m_endPos;		//�I�_�̍��W
	CVector3		m_color;		//�F(x,y,z) = (r,g,b)
	CPrimitive		m_primitive;	//�v���~�e�B�u
	CShader			m_ps;			//�s�N�Z���V�F�[�_�[
	CShader			m_vs;			//���_�V�F�[�_�[
	CConstantBuffer m_cb;			//�萔�o�b�t�@
};