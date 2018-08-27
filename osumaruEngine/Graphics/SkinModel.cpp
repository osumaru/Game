#include "engineStdafx.h"
#include "SkinModel.h"
#include "Skelton.h"
#include "Animation.h"

SkinModel::SkinModel()
{
}

SkinModel::~SkinModel()
{
}

void SkinModel::Load(wchar_t* filePath, Animation* animation)
{
	std::unique_ptr<Skelton> skelton;
	skelton = std::make_unique<Skelton>();
	SkinModelCB cb;
	cb.worldMat = Matrix::Identity;
	cb.viewMat.MakeLookAt({ 0.0f, 0.0f, -100.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f });
	cb.projMat.MakeProjectionMatrix(Math::DegToRad(60.0f), 1.0f, 1.0f, 500.0f);
	constantBuffer.Create(sizeof(SkinModelCB), &cb);
	size_t pos = wcslen(filePath);
	
	wchar_t skeltonName[256] = {0};
	wcsncpy(skeltonName, filePath, pos - 4);
	wcscat(skeltonName, L".tks");
	if (skelton->Load(skeltonName))
	{
		if (animation != nullptr)
		{
			animation->SetSkelton(skelton.get());
		}
		m_skelton = std::move(skelton);
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
		m_skinModel = Model::CreateFromCMO(GetDevice(), filePath, effectFactory, false, false, onFindBone);
	}
	else
	{
		SkinModelEffectFactory effectFactory(GetDevice());
		m_skinModel = Model::CreateFromCMO(GetDevice(), filePath, effectFactory);
	}
}

void SkinModel::Update(Vector3 position, Quaternion rotation, Vector3 scale)
{
	Matrix posMat;
	posMat.MakeTranslation(position);
	Matrix rotMat;
	rotMat.MakeRotationFromQuaternion(rotation);
	Matrix scaleMat;
	scaleMat.MakeScaling(scale);
	worldMatrix.Mul(scaleMat, rotMat);
	worldMatrix.Mul(worldMatrix, posMat);
	if (m_skelton != nullptr)
	{
		m_skelton->Update(worldMatrix);
	}
}


void SkinModel::Draw(Matrix view, Matrix projection)
{
	DirectX::CommonStates common(GetDevice());
	Matrix world = Matrix::Identity;
	SkinModelCB cb;
	cb.viewMat = view;
	cb.projMat = projection;
	cb.worldMat = worldMatrix;
	constantBuffer.Update(&cb);
	ID3D11Buffer* cbBuffer = constantBuffer.GetBody();
	GetDeviceContext()->VSSetConstantBuffers(0, 1, &cbBuffer);
	if (m_skelton != nullptr)
	{
		m_skelton->Render();
	}
	m_skinModel->Draw(GetDeviceContext(), common, world, view, projection);
}