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



private:
	std::vector<DWORD>									m_indexBuffer;
	std::vector<Vector3>								m_vertexBuffer;
	std::unique_ptr<btBvhTriangleMeshShape>				m_meshShape;				//メッシュコライダー
	std::unique_ptr<btTriangleIndexVertexArray>			m_stridingMeshInterface;
};