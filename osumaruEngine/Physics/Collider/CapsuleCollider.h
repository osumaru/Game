#pragma once
#include "ICollider.h"
//�J�v�Z���R���C�_�[

class CCapsuleCollider : public ICollider
{
public:
	//�R���X�g���N�^
	CCapsuleCollider();

	//�f�X�g���N�^
	~CCapsuleCollider();

	/*
	�R���C�_�[����鏉�����֐�
	radius		�R���C�_�[�̔��a
	height		�R���C�_�[�̍���
	*/
	void Create(float radius, float height)
	{
		m_shape.reset(new btCapsuleShape(radius, height));
	}

	//�R���C�_�[���擾
	const btCollisionShape* GetBody() const override
	{
		return m_shape.get();
	}

private:
	std::unique_ptr<btCapsuleShape>		m_shape;	//�R���C�_�[
};