#pragma once
#pragma once
#include "../Graphics/Primitive.h"
#include "../Graphics/Shader.h"

struct SRigidBodyVSLayout
{
	CVector4 pos;
	CVector3 color;
};
//���̂�\������N���X

class CRigidBodyDraw : public btIDebugDraw
{
public:
	//�R���X�g���N�^
	CRigidBodyDraw();

	//�f�X�g���N�^
	~CRigidBodyDraw();

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
	void Draw(CMatrix viewMatrix, CMatrix projectionMatrix);

	//�悭�킩���ĂȂ�
	void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) {}

	//�悭�킩���ĂȂ�
	void reportErrorWarning(const char* warningString) {}

	//�悭�킩���ĂȂ�
	void draw3dText(const btVector3& location, const char* textString) {}

	//�悭�킩���ĂȂ�
	void setDebugMode(int debugMode) {}

	//�J�E���g�����Z�b�g
	void Reset()
	{
		//���t���[���C���f�b�N�X�o�b�t�@�ƒ��_�o�b�t�@�����Z�b�g
		m_count = 0;
	}

	//�悭�킩���ĂȂ�
	int getDebugMode() const
	{
		return 0;
	}

private:
	static const int VERTEX_NUM = 10000;
	SRigidBodyVSLayout m_vertexBuffer[VERTEX_NUM];
	DWORD m_indexBuffer[VERTEX_NUM];
	CPrimitive		m_primitive;			//�v���~�e�B�u
	int				m_count;				//�v���~�e�B�u�̐�
	CShader			m_vs;				//�G�t�F�N�g
	CShader			m_ps;
	CConstantBuffer	m_cb;
};