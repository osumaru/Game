#include "engineStdafx.h"
#include "SkinModel.h"
#include "Skelton.h"
#include "Animation.h"
#include "SkinModelEffect.h"

CSkinModel::CSkinModel()
{
}

CSkinModel::~CSkinModel()
{
}

void CSkinModel::Load(const wchar_t* filePath, CAnimation* animation)
{
	m_skelton = nullptr;
	std::unique_ptr<CSkelton> skelton;
	skelton = std::make_unique<CSkelton>();
	//コンスタントバッファを作成
	SSkinModelCB cb;
	cb.worldMat = CMatrix::Identity;
	cb.viewProjMat = CMatrix::Identity;
	cb.isNormalMap = m_isNormalMap;
	constantBuffer.Create(sizeof(SSkinModelCB), &cb);
	m_lightCB.Create(sizeof(CLight), &m_light);
	Engine().GetDeferred().SetConstantBuffer();
	//ファイル名の拡張子(cmo)を除きtksを追加しスケルトンのファイル名を作成
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
	}
	m_skinModel = SkinmodelResource().Load(filePath, m_skelton.get());
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
	Engine().GetShadowMap().AddModel(this);
}


void CSkinModel::Draw(const CMatrix& view, const CMatrix& projection, bool isShadow)
{
	DirectX::CommonStates common(GetDevice());
	CMatrix world = CMatrix::Identity;
	Engine().SetAlphaBlendState(enAlphaBlendState3D);
	Engine().SetDepthStencilState(enDepthStencilState3D);
	SSkinModelCB cb;
	CMatrix viewProjMat;
	viewProjMat.Mul(view, projection);
	cb.viewProjMat = viewProjMat;
	cb.worldMat = worldMatrix;
	cb.isNormalMap = m_isNormalMap;
	constantBuffer.Update(&cb);
	m_lightCB.Update(&m_light);
	ID3D11Buffer* cbBuffer = constantBuffer.GetBody();
	GetDeviceContext()->VSSetConstantBuffers(0, 1, &cbBuffer);
	GetDeviceContext()->PSSetConstantBuffers(0, 1, &cbBuffer);
	cbBuffer = m_lightCB.GetBody();
	GetDeviceContext()->PSSetConstantBuffers(1, 1, &cbBuffer);
	if (m_pNormalTexture != nullptr)
	{
		ID3D11ShaderResourceView* srv = m_pNormalTexture->GetShaderResource();
		GetDeviceContext()->PSSetShaderResources(11, 1, &srv);
	}
	if (m_skelton != nullptr)
	{
		m_skelton->Render();
	}
	for (auto& modelMesh : m_skinModel->meshes)
	{
		for (auto& meshPart : modelMesh->meshParts)
		{
			((ISkinModelEffect*)(&*meshPart->effect))->SetIsShadow(isShadow);
		}
	}
	m_skinModel->Draw(GetDeviceContext(), common, world, view, projection);
	
}

const CMatrix& CSkinModel::FindBoneWorldMatrix(const wchar_t* boneName) const
{
	const CBone* bone = m_skelton->FindBone(boneName);
	if (bone != nullptr)
	{
		return bone->GetWorldMatrix();


	}
	return CMatrix::Identity;
}

void CSkinModel::LoadNormalmap(const wchar_t * filePath)
{
	m_pNormalTexture = TextureResource().LoadTexture(filePath);
	m_isNormalMap = 1;
}
