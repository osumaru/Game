#pragma once
//�R���C�_�[�̊��N���X

class ICollider : Uncopyable
{
public:
	virtual const btCollisionShape* GetBody() const = 0;
};