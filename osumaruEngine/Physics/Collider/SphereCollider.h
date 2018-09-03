#pragma once
#include "ICollider.h"
//���`��̃R���C�_�[�N���X

class CSphereCollider : public ICollider
{
public:

	//�R���X�g���N�^
	CSphereCollider();
	
	//�f�X�g���N�^
	~CSphereCollider();

	/*
	�R���C�_�[���쐬
	radius		���̔��a
	*/
	void Create(float radius);

	//�R���C�_�[���擾
	const btSphereShape* GetBody() const override
	{
		return m_sphereShape.get();
	}

private:
	std::unique_ptr<btSphereShape> m_sphereShape;	//���̃R���C�_�[
};