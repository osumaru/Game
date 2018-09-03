#include "engineStdafx.h"
#include "MeshCollider.h"
#include "../../Graphics/SkinModel.h"

void CMeshCollider::CreateCollider(CSkinModel* skinModel)
{
	DirectX::Model* model = skinModel->GetBody();
	m_stridingMeshInterface.reset(new btTriangleIndexVertexArray);
	m_aabbMax = { FLT_MIN, FLT_MIN, FLT_MIN };
	m_aabbMin = { FLT_MAX, FLT_MAX, FLT_MAX };
	for (auto& mesh : model->meshes)
	{
		for (auto& meshPart : mesh->meshParts)
		{
			ID3D11Buffer* vertexBuffer = meshPart->vertexBuffer.Get();
			D3D11_BUFFER_DESC vertexDesc;
			vertexBuffer->GetDesc(&vertexDesc);

			
			int vertexCount = vertexDesc.ByteWidth / meshPart->vertexStride;


			D3D11_MAPPED_SUBRESOURCE subresource;
			Engine().GetDeviceContext()->Map(vertexBuffer, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &subresource);
			char* pData = (char*)subresource.pData;
			for (int i = 0;i < vertexCount;i++)
			{
				CVector3 vertexPos = *((CVector3*)pData);
				m_aabbMax.Max(vertexPos);
				m_aabbMin.Min(vertexPos);
				m_vertexBuffer.push_back(vertexPos);
				pData += meshPart->vertexStride;
			}
			Engine().GetDeviceContext()->Unmap(vertexBuffer, 0);


			ID3D11Buffer* indexBuffer = meshPart->indexBuffer.Get();
			D3D11_BUFFER_DESC indexDesc;
			indexBuffer->GetDesc(&indexDesc);
			HRESULT hr = Engine().GetDeviceContext()->Map(indexBuffer, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &subresource);
			pData = (char*)subresource.pData;
			int indexStride = 0;
			switch (meshPart->indexFormat)
			{
			case DXGI_FORMAT_R16_UINT:
				indexStride = 2;
				break;
			case DXGI_FORMAT_R32_UINT:
				indexStride = 4;
				break;
			}
			vertexCount = indexDesc.ByteWidth / indexStride;
			for (int i = 0;i < vertexCount;i++)
			{	
				unsigned int value = 0;
				if (indexStride == 2)
				{
					value = (unsigned int)*((unsigned short*)pData);
					m_indexBuffer.push_back(value);
				}
				else if (indexStride == 4)
				{
					value = *((unsigned int*)pData);
					m_indexBuffer.push_back(value);
				}
				pData += indexStride;
			}

		}
	}
	btIndexedMesh indexedMesh;
	indexedMesh.m_numTriangles = m_indexBuffer.size() / 3;
	indexedMesh.m_triangleIndexBase = (unsigned char*)&m_indexBuffer[0];
	indexedMesh.m_triangleIndexStride = 12;
	indexedMesh.m_numVertices = (unsigned int)m_vertexBuffer.size();
	indexedMesh.m_vertexBase = (unsigned char*)&m_vertexBuffer[0];
	indexedMesh.m_vertexStride = sizeof(CVector3);
	m_stridingMeshInterface->addIndexedMesh(indexedMesh);
	m_meshShape.reset(new btBvhTriangleMeshShape(m_stridingMeshInterface.get(), true));
	
}