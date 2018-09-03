#pragma once
#include "ICollider.h"
class CSkinModel;

class CMeshCollider : public ICollider
{
public:

	void CreateCollider(CSkinModel* skinModel);

	const btCollisionShape* GetBody()const override
	{
		return m_meshShape.get();
	}

	CVector3 GetAabbMax()
	{
		return m_aabbMax;
	}

	CVector3 GetAabbMin()
	{
		return m_aabbMin;
	}

private:
	CVector3												m_aabbMax;
	CVector3												m_aabbMin;

	std::vector<DWORD>									m_indexBuffer;
	std::vector<CVector3>								m_vertexBuffer;
	std::unique_ptr<btBvhTriangleMeshShape>				m_meshShape;				//メッシュコライダー
	std::unique_ptr<btTriangleIndexVertexArray>			m_stridingMeshInterface;
};