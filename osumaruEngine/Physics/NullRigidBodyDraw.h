#pragma once
#include "IRigidBodyDraw.h"

class NullRigidBodyDraw : public IRigidBodyDraw
{
public:
	NullRigidBodyDraw()
	{

	}

	~NullRigidBodyDraw()override
	{

	}

	//�������֐�
	void Init()override
	{

	}

	/*
	���_��ǉ�����֐�
	from	1�ڂ̒��_
	to		2�ڂ̒��_
	color	�v���~�e�B�u�̐F
	*/
	void drawLine(const btVector3 &from, const btVector3 &to, const btVector3& color)override
	{

	}

	/*
	�`��֐�
	viewMatrix			�J�����̃r���[�s��
	projectionMatrix	�J�����̎ˉe�s��
	*/
	void Draw(CMatrix viewMatrix, CMatrix projectionMatrix)override
	{

	}

	//�J�E���g�����Z�b�g
	void Reset() override
	{

	}

};

