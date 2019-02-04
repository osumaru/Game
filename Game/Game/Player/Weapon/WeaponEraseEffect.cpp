#include "WeaponEraseEffect.h"
#include "../Player.h"
#include "../../Camera/GameCamera.h"

void CWeaponEraseEffect::Init(const CSkinModel* skinmodel[enWeaponNum])
{
	int maxVertexSize = 0;
	int maxIndexSize = 0;
	for (int i = 0; i < enWeaponNum; i++)
	{
		std::vector<unsigned int> indexBufferVector;
		DirectX::Model* model = skinmodel[i]->GetBody();
		//メッシュをなめる
		for (auto& mesh : model->meshes)
		{
			for (auto& meshPart : mesh->meshParts)
			{
				ID3D11Buffer* vertexBuffer = meshPart->vertexBuffer.Get();
				D3D11_BUFFER_DESC vertexDesc;
				vertexBuffer->GetDesc(&vertexDesc);

				//頂点数を求める
				int vertexCount = vertexDesc.ByteWidth / meshPart->vertexStride;

				//頂点バッファを取得
				D3D11_MAPPED_SUBRESOURCE subresource;
				Engine().GetDeviceContext()->Map(vertexBuffer, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &subresource);
				//頂点バッファから座標を取得して配列に積む
				char* pData = (char*)subresource.pData;
				for (int j = 0; j < vertexCount; j++)
				{
					CVector3 vertexPos = *((CVector3*)pData);

					m_weaponVertexBuffer[i].push_back(vertexPos);
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
				for (int j = 0; j < vertexCount; j++)
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

		for (int j = 0; j < indexBufferVector.size(); j += 3)
		{
			m_weaponIndexBuffer[i].push_back(indexBufferVector[j]);
			m_weaponIndexBuffer[i].push_back(indexBufferVector[j + 1]);
			m_weaponIndexBuffer[i].push_back(indexBufferVector[j]);
			m_weaponIndexBuffer[i].push_back(indexBufferVector[j + 2]);
			m_weaponIndexBuffer[i].push_back(indexBufferVector[j + 1]);
			m_weaponIndexBuffer[i].push_back(indexBufferVector[j + 2]);
		}
		maxVertexSize = max(maxVertexSize, m_weaponVertexBuffer[i].size());
		maxIndexSize = max(maxIndexSize, m_weaponIndexBuffer[i].size());
	}

	
	m_vertexBuffer.resize(maxVertexSize);
	m_indexBuffer.resize(maxIndexSize);
	ZeroMemory(&m_vertexBuffer[0], sizeof(m_vertexBuffer));
	ZeroMemory(&m_indexBuffer[0], sizeof(m_indexBuffer));
	m_primitive.Create(&m_vertexBuffer[0], sizeof(SVSLayout), maxVertexSize, &m_indexBuffer[0], maxIndexSize, CPrimitive::enIndex16, CPrimitive::enTypeLineList);
	m_vs.Load("Assets/shader/line.fx", "VSEraseEffect", CShader::enVS);
	m_ps.Load("Assets/shader/line.fx", "PSEraseEffect", CShader::enPS);
	CMatrix mat = CMatrix::Identity;
	m_cb.Create(sizeof(CMatrix), &mat);
	float alpha = 0.0f;
	m_alphaCB.Create(sizeof(float), &alpha);
}

void CWeaponEraseEffect::SetWorldMatrix(const CMatrix& mat, EnPlayerWeapon weaponNum)
{
	ZeroMemory(&m_vertexBuffer[0], sizeof(m_vertexBuffer));
	ZeroMemory(&m_indexBuffer[0], sizeof(m_indexBuffer));
	for (int i = 0;i < m_weaponVertexBuffer[weaponNum].size();i++)
	{
		SVSLayout vsLayout;
		CVector3 position;
		position = m_weaponVertexBuffer[weaponNum][i];
		position.Mul(mat);
		vsLayout.position = { position.x, position.y, position.z, 1.0f };
		vsLayout.color = { 0.0f, 0.0f, 90.0f };
		vsLayout.dissolve = Random().GetRandDouble();
		m_vertexBuffer[i] = vsLayout;
	}
	for (int i = 0; i < m_weaponIndexBuffer[weaponNum].size(); i++)
	{
		m_indexBuffer[i] = m_weaponIndexBuffer[weaponNum][i];
	}

	m_primitive.Update(&m_vertexBuffer[0], &m_indexBuffer[0]);
}

void CWeaponEraseEffect::Draw()
{
	if (!m_isDraw)
	{
		return;
	}

	const CCamera& camera = GetGameCamera().GetCamera();
	CMatrix mat;
	mat.Mul(camera.GetViewMatrix(), camera.GetProjectionMatrix());
	m_cb.Update(&mat);
	m_alphaCB.Update(&m_dissolve);
	EnAlphaBlendState backupBlend = Engine().GetCurrentAlphaBlendState();
	Engine().SetAlphaBlendState(enAlphaBlendStateAdd);

	//描画
	GetDeviceContext()->PSGetConstantBuffers(1, 1, m_alphaCB.GetBody().GetAddressOf());
	GetDeviceContext()->VSSetConstantBuffers(0, 1, m_cb.GetBody().GetAddressOf());
	GetDeviceContext()->VSSetShader((ID3D11VertexShader*)m_vs.GetBody().Get(), nullptr, 0);
	GetDeviceContext()->PSSetShader((ID3D11PixelShader*)m_ps.GetBody().Get(), nullptr, 0);
	GetDeviceContext()->IASetInputLayout(m_vs.GetInputlayOut().Get());

	m_primitive.Draw(GetDeviceContext());
	Engine().SetAlphaBlendState(backupBlend);
}