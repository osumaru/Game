#include "NavigationMesh.h"
#include "Graphics/SkinModel.h"
#include "Physics/Physics.h"
#include "Physics/RigidBodyDraw.h"

void CNavigationMesh::Init()
{
	std::vector<CVector3> vertexBufferVector;
	std::vector<unsigned int> indexBufferVector;
	DirectX::Model* model = m_pModel->GetBody();
	CVector3 aabbMax = {FLT_MIN, FLT_MIN, FLT_MIN};
	CVector3 aabbMin = { FLT_MAX, FLT_MAX, FLT_MAX };
	CMatrix mat = m_pModel->GetWorldMatrix();
	CVector3 transManip = { mat.m[3][0], mat.m[3][1], mat.m[3][2] };
	//メッシュをなめる
	for (auto& mesh : model->meshes)
	{
		for (auto& meshPart : mesh->meshParts)
		{
			ID3D11Buffer* vertexBuffer = meshPart->vertexBuffer.Get();
			D3D11_BUFFER_DESC vertexDesc;
			vertexBuffer->GetDesc(&vertexDesc);

			//超点数を求める
			int vertexCount = vertexDesc.ByteWidth / meshPart->vertexStride;

			//頂点バッファを取得
			D3D11_MAPPED_SUBRESOURCE subresource;
			Engine().GetDeviceContext()->Map(vertexBuffer, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &subresource);
			//頂点バッファから座標を取得して配列に積む
			char* pData = (char*)subresource.pData;
			for (int i = 0; i < vertexCount; i++)
			{
				CVector3 vertexPos = *((CVector3*)pData);
				vertexPos += transManip;
				aabbMax.Max(vertexPos);
				aabbMin.Min(vertexPos);
				vertexBufferVector.push_back(vertexPos);
				pData += meshPart->vertexStride;
			}
			Engine().GetDeviceContext()->Unmap(vertexBuffer, 0);


			//インデックスバッファを取得
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

			//インデックスバッファからインデックス情報を取得して配列に積む
			for (int i = 0; i < vertexCount; i++)
			{
				unsigned int value = 0;
				if (indexStride == 2)
				{
					value = (unsigned int)*((unsigned short*)pData);
					indexBufferVector.push_back(value);
				}
				else if (indexStride == 4)
				{
					value = *((unsigned int*)pData);
					indexBufferVector.push_back(value);
				}
				pData += indexStride;
			}
		}
	}
	CVector3 aabb = aabbMax - aabbMin;

	//頂点情報を使ってメッシュデータの作成
	for (int i = 0; i < indexBufferVector.size(); i += 3)
	{
		CVector3 poligonPos = CVector3::Zero;
		bool isContinue = false;
		for (int j = 0; j < 3; j++)
		{
			CVector3 vertexPos = vertexBufferVector[indexBufferVector[i + j]];
			for (auto& obs : m_obstacleObjects)
			{
				CVector3 aabbMin = obs.aabbMin + obs.center;
				CVector3 aabbMax = obs.aabbMax + obs.center;
				if (aabbMin.x <= vertexPos.x && vertexPos.x <= aabbMax.x &&
					aabbMin.z <= vertexPos.z && vertexPos.z <= aabbMax.z)
				{
					isContinue = true;
					break;
				}
			}
			if (isContinue)
			{
				break;
			}
			poligonPos += vertexPos;
		}
		if (isContinue)
		{
			continue;
		}
		poligonPos.Div(3.0f);
		//aabbのxzで割りどのエリアに属するポリゴンか決める
		CVector3 localPos = poligonPos - aabbMin;
		localPos.x = localPos.x / aabb.x * AREA_NUM;
		localPos.z = localPos.z / aabb.z * AREA_NUM;
		m_meshData[(int)localPos.x][(int)localPos.z].push_back({ poligonPos,  vertexBufferVector[indexBufferVector[i + 0]], vertexBufferVector[indexBufferVector[i + 1]], vertexBufferVector[indexBufferVector[i + 2]] });
	}
}


void CNavigationMesh::Draw()
{
	for (int i = 0; i < AREA_NUM; i++)
	{
		for (int j = 0; j < AREA_NUM; j++)
		{
			for (auto& mesh : m_meshData[i][j])
			{

				btVector3 v1;
				v1.setX(mesh.vertexPos[0].x);
				v1.setY(mesh.vertexPos[0].y);
				v1.setZ(mesh.vertexPos[0].z);
				btVector3 v2;
				v2.setX(mesh.vertexPos[1].x);
				v2.setY(mesh.vertexPos[1].y);
				v2.setZ(mesh.vertexPos[1].z);
				PhysicsWorld().GetRigidBodyDraw().drawLine(v1, v2, btVector3(0.0f, 0.0f, 0.0f));

				v1.setX(mesh.vertexPos[1].x);
				v1.setY(mesh.vertexPos[1].y);
				v1.setZ(mesh.vertexPos[1].z);
				v2.setX(mesh.vertexPos[2].x);
				v2.setY(mesh.vertexPos[2].y);
				v2.setZ(mesh.vertexPos[2].z);
				PhysicsWorld().GetRigidBodyDraw().drawLine(v1, v2, btVector3(0.0f, 0.0f, 0.0f));

				v1.setX(mesh.vertexPos[0].x);
				v1.setY(mesh.vertexPos[0].y);
				v1.setZ(mesh.vertexPos[0].z);
				v2.setX(mesh.vertexPos[2].x);
				v2.setY(mesh.vertexPos[2].y);
				v2.setZ(mesh.vertexPos[2].z);
				PhysicsWorld().GetRigidBodyDraw().drawLine(v1, v2, btVector3(0.0f, 0.0f, 0.0f));
			}
		}
	}
}