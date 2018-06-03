#pragma once
#include "ICollider.h"

class CapsuleCollider : public ICollider
{
public:
	//�R���X�g���N�^
	CapsuleCollider();

	//�f�X�g���N�^
	~CapsuleCollider();

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