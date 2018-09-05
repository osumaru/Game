#pragma once
#include "ICollider.h"
class CSkinModel;
//���b�V���R���C�_�[

class CMeshCollider : public ICollider
{
public:

	/*
	���b�V���R���C�_�[�����
	skinModel	���ƂȂ郂�f��
	*/
	void CreateCollider(CSkinModel* skinModel);

	/*
	�R���C�_�[���擾
	*/
	const btCollisionShape* GetBody()const override
	{
		return m_meshShape.get();
	}


	//���b�V������AABB�̍ő�l���擾
	const CVector3& GetAabbMax() const 
	{
		return m_aabbMax;
	}
	//���b�V������AABB�̍ŏ��l���擾
	const CVector3& GetAabbMin() const
	{
		return m_aabbMin;
	}

private:
	CVector3											m_aabbMax;					//AABB�̍ő�l
	CVector3											m_aabbMin;					//AABB�̍ŏ��l
	std::vector<DWORD>									m_indexBuffer;				//�C���f�b�N�X�o�b�t�@
	std::vector<CVector3>								m_vertexBuffer;				//���_�o�b�t�@
	std::unique_ptr<btBvhTriangleMeshShape>				m_meshShape;				//���b�V���R���C�_�[
	std::unique_ptr<btTriangleIndexVertexArray>			m_stridingMeshInterface;	//���b�V���C���^�[�t�F�[�X
};