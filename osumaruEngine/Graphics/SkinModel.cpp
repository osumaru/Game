#include "engineStdafx.h"
#include "SkinModel.h"
#include "Skelton.h"
#include "Animation.h"

CSkinModel::CSkinModel()
{
}

CSkinModel::~CSkinModel()
{
}

void CSkinModel::Load(wchar_t* filePath, CAnimation* animation)
{
	std::unique_ptr<CSkelton> skelton;
	skelton = std::make_unique<CSkelton>();
	SSkinModelCB cb;
	cb.worldMat = CMatrix::Identity;
	cb.viewProjMat = CMatrix::Identity;
	constantBuffer.Create(sizeof(SSkinModelCB), &cb);
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
		CSkinModelEffectFactory effectFactory(GetDevice());
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
		CSkinModelEffectFactory effectFactory(GetDevice());
		m_skinModel = Model::CreateFromCMO(GetDevice(), filePath, effectFactory);
	}
}

void CSkinModel::Update(const CVector3& position, const CQuaternion& rotation, const CVector3& scale, bool isZup)
{

	CMatrix biMat = CMatrix::Identity;
	if (isZup)
	{
		CQuaternion rot;
		rot.SetRotationDeg(CVector3::AxisX, -90.0f);
		biMat.MakeRotationFromQuaternion(rot);
	}
	CMatrix posMat;
	posMat.MakeTranslation(position);
	CMatrix rotMat;
	rotMat.MakeRotationFromQuaternion(rotation);
	CMatrix scaleMat;
	scaleMat.MakeScaling(scale);
	worldMatrix.Mul(scaleMat, biMat);
	worldMatrix.Mul(worldMatrix, rotMat);
	worldMatrix.Mul(worldMatrix, posMat);
	
	if (m_skelton != nullptr)
	{
		m_skelton->Update(worldMatrix);
	}
}


void CSkinModel::Draw(const CMatrix& view, const CMatrix& projection)
{
	DirectX::CommonStates common(GetDevice());
	CMatrix world = CMatrix::Identity;
	SSkinModelCB cb;
	CMatrix viewProjMat;
	viewProjMat.Mul(view, projection);
	cb.viewProjMat = viewProjMat;
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

const CMatrix& CSkinModel::FindBoneWorldMatrix(wchar_t* boneName)
{
	CBone* bone = m_skelton->FindBone(boneName);
	if (bone != nullptr)
	{
		return bone->GetWorldMatrix();


	}
	return CMatrix::Identity;
}