#pragma once
#include "ICollider.h"
class CSkinModel;
//メッシュコライダー

class CMeshCollider : public ICollider
{
public:

	/*
	メッシュコライダーを作る
	skinModel	元となるモデル
	*/
	void CreateCollider(CSkinModel* skinModel);

	/*
	コライダーを取得
	*/
	const btCollisionShape* GetBody()const override
	{
		return m_meshShape.get();
	}


	//メッシュを包むAABBの最大値を取得
	const CVector3& GetAabbMax() const 
	{
		return m_aabbMax;
	}
	//メッシュを包むAABBの最小値を取得
	const CVector3& GetAabbMin() const
	{
		return m_aabbMin;
	}

private:
	CVector3											m_aabbMax;					//AABBの最大値
	CVector3											m_aabbMin;					//AABBの最小値
	std::vector<DWORD>									m_indexBuffer;				//インデックスバッファ
	std::vector<CVector3>								m_vertexBuffer;				//頂点バッファ
	std::unique_ptr<btBvhTriangleMeshShape>				m_meshShape;				//メッシュコライダー
	std::unique_ptr<btTriangleIndexVertexArray>			m_stridingMeshInterface;	//メッシュインターフェース
};