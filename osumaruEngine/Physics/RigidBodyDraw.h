#pragma once
#pragma once
#include "../Graphics/Primitive.h"
#include "../Graphics/Shader.h"
#include "IRigidBodyDraw.h"

struct SRigidBodyVSLayout
{
	CVector4 pos;
	CVector3 color;
};
//���̂�\������N���X

class CRigidBodyDraw : public IRigidBodyDraw
{
public:
	//�R���X�g���N�^
	CRigidBodyDraw();

	//�f�X�g���N�^
	~CRigidBodyDraw() override;

	//�������֐�
	void Init();

	/*
	���_��ǉ�����֐�
	from	1�ڂ̒��_
	to		2�ڂ̒��_
	color	�v���~�e�B�u�̐F
	*/
	void drawLine(const btVector3 &from, const btVector3 &to, const btVector3& color)override;

	/*
	�`��֐�
	viewMatrix			�J�����̃r���[�s��
	projectionMatrix	�J�����̎ˉe�s��
	*/
	void Draw(CMatrix viewMatrix, CMatrix projectionMatrix)override;


	//�J�E���g�����Z�b�g
	void Reset() override
	{
		ZeroMemory(m_vertexBuffer, sizeof(m_vertexBuffer));
		ZeroMemory(m_indexBuffer, sizeof(m_indexBuffer));
		//���t���[���C���f�b�N�X�o�b�t�@�ƒ��_�o�b�t�@�����Z�b�g
		m_count = 0;
	}

private:
	static const int VERTEX_NUM = 100000;
	SRigidBodyVSLayout m_vertexBuffer[VERTEX_NUM];
	DWORD m_indexBuffer[VERTEX_NUM];
	CPrimitive		m_primitive;			//�v���~�e�B�u
	int				m_count;				//�v���~�e�B�u�̐�
	CShader			m_vs;				//�G�t�F�N�g
	CShader			m_ps;
	CConstantBuffer	m_cb;
};