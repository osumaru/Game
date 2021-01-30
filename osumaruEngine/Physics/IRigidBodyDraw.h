#pragma once
class IRigidBodyDraw : public btIDebugDraw
{
public:
	IRigidBodyDraw();
	virtual ~IRigidBodyDraw();
	//�������֐�
	virtual void Init() = 0;

	/*
	���_��ǉ�����֐�
	from	1�ڂ̒��_
	to		2�ڂ̒��_
	color	�v���~�e�B�u�̐F
	*/
	virtual void drawLine(const btVector3 &from, const btVector3 &to, const btVector3& color) = 0;

	/*
	�`��֐�
	viewMatrix			�J�����̃r���[�s��
	projectionMatrix	�J�����̎ˉe�s��
	*/
	virtual void Draw(CMatrix viewMatrix, CMatrix projectionMatrix) = 0;

	//�悭�킩���ĂȂ�
	void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) override final
	{
	}

	//�悭�킩���ĂȂ�
	void reportErrorWarning(const char* warningString) override final
	{
	}

	//�悭�킩���ĂȂ�
	void draw3dText(const btVector3& location, const char* textString) override final
	{
	}

	//�悭�킩���ĂȂ�
	void setDebugMode(int debugMode) override final
	{
	}

	//�J�E���g�����Z�b�g
	virtual void Reset() = 0;

	//�悭�킩���ĂȂ�
	int getDebugMode() const override final
	{
		return 0;
	}
};

