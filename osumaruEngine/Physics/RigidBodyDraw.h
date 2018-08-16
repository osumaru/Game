#pragma once
#pragma once
#include "../Graphics/Primitive.h"
#include "../Graphics/Shader.h"

struct RigidBodyVSLayout
{
	Vector4 pos;
	Vector3 color;
};
//���̂�\������N���X

class RigidBodyDraw : public btIDebugDraw
{
public:
	//�R���X�g���N�^
	RigidBodyDraw();

	//�f�X�g���N�^
	~RigidBodyDraw();

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
	void Draw(Matrix viewMatrix, Matrix projectionMatrix);

	//�悭�킩���ĂȂ�
	void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) {}

	//�悭�킩���ĂȂ�
	void reportErrorWarning(const char* warningString) {}

	//�悭�킩���ĂȂ�
	void draw3dText(const btVector3& location, const char* textString) {}

	//�悭�킩���ĂȂ�
	void setDebugMode(int debugMode) {}

	void Reset()
	{
		//���t���[���C���f�b�N�X�o�b�t�@�ƒ��_�o�b�t�@�����Z�b�g
		m_count = 0;
		m_vertexBuffer.clear();
		m_indexBuffer.clear();
	}

	//�悭�킩���ĂȂ�
	int getDebugMode() const
	{
		return 0;
	}

private:
	std::vector<DWORD> m_indexBuffer;			//�C���f�b�N�X�o�b�t�@
	std::vector<RigidBodyVSLayout> m_vertexBuffer;	//���_�o�b�t�@
	Primitive		m_primitive;			//�v���~�e�B�u
	int				m_count;				//�v���~�e�B�u�̐�
	Shader			m_vs;				//�G�t�F�N�g
	Shader			m_ps;
	ConstantBuffer	m_cb;
};