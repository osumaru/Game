#pragma once
#include "ICollider.h"
class SkinModel;

class MeshCollider : public ICollider
{
public:

	void CreateCollider(SkinModel* skinModel);

	const btCollisionShape* GetBody()const override
	{
		return m_meshShape.get();
	}

	Vector3 GetAabbMax()
	{
		return m_aabbMax;
	}

	Vector3 GetAabbMin()
	{
		return m_aabbMin;
	}

private:
	Vector3												m_aabbMax;
	Vector3												m_aabbMin;

	std::vector<DWORD>									m_indexBuffer;
	std::vector<Vector3>								m_vertexBuffer;
	std::unique_ptr<btBvhTriangleMeshShape>				m_meshShape;				//メッシュコライダー
	std::unique_ptr<btTriangleIndexVertexArray>			m_stridingMeshInterface;
};