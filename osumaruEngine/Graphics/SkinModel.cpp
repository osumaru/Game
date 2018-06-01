#include "engineStdafx.h"
#include "SkinModel.h"
#include "Skelton.h"

SkinModel::SkinModel()
{
}

void SkinModel::Create()
{
	m_skelton = new Skelton;
	m_skelton->Init();
	SkinModelCB cb;
	cb.worldMat = Matrix::Identity;
	cb.viewMat.MakeLookAt({ 0.0f, 0.0f, -100.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f });
	cb.projMat.MakeProjectionMatrix(Math::DegToRad(60.0f), 1.0f, 1.0f, 500.0f);
	constantBuffer.Create(sizeof(SkinModelCB), &cb);
	std::vector<std::unique_ptr<Bone>>& bones = m_skelton->GetBones();
	Matrix* boneMatrix = new Matrix[bones.size()];
	for (int i = 0;i < bones.size();i++)
	{
		boneMatrix[i] = bones[i]->GetWorldMatrix();
	}
	D3D11_BUFFER_DESC desc;
	desc.ByteWidth = bones.size() * sizeof(Matrix);
	desc.StructureByteStride = sizeof(Matrix);
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	D3D11_SUBRESOURCE_DATA resource;
	resource.pSysMem = boneMatrix;

	GetDevice()->CreateBuffer(&desc, &resource, &m_structuredBuffer);
	D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc;
	ZeroMemory(&viewDesc, sizeof(viewDesc));
	viewDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
	viewDesc.Format = DXGI_FORMAT_UNKNOWN;
	viewDesc.BufferEx.FirstElement = 0;
	viewDesc.BufferEx.NumElements = bones.size();
	GetDevice()->CreateShaderResourceView(m_structuredBuffer, &viewDesc, &m_shaderResourceView);

	SkinModelEffectFactory effectFactory(GetDevice());
	auto onFindBone = [&](
		const wchar_t* boneName,
		const VSD3DStarter::Bone* bone,
		std::vector<int>& localBoneIDtoGlobalBoneIDTbl
		) {
		int globalBoneID = m_skelton->FindBoneID(boneName);
		if (globalBoneID == -1) {
			return;
		}
		localBoneIDtoGlobalBoneIDTbl.push_back(globalBoneID);
	};
	m_skinModel = Model::CreateFromCMO(GetDevice(), L"Assets/modelData/Unitychan.cmo", effectFactory, false, false, onFindBone);

}

void SkinModel::Draw(Matrix view, Matrix projection)
{
	DirectX::CommonStates common(GetDevice());
	Matrix world = Matrix::Identity;
	SkinModelCB cb;
	cb.viewMat = view;
	cb.projMat = projection;
	cb.worldMat = world;
	constantBuffer.Update(&cb);
	ID3D11Buffer* cbBuffer = constantBuffer.GetBody();
	GetDeviceContext()->VSSetConstantBuffers(0, 1, &cbBuffer);
	GetDeviceContext()->VSSetShaderResources(0, 1, &m_shaderResourceView);
	m_skinModel->Draw(GetDeviceContext(), common, world, view, projection);
}