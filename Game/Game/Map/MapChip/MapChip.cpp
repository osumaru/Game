#include "stdafx.h"
#include "MapChip.h"
#include "../../GameCamera.h"

MapChip::MapChip():
	m_position(0.0f, 0.0f, 0.0f),
	m_rotation(0.0f, 0.0f, 0.0f, 1.0f),
	m_scale(1.0f, 1.0f, 1.0f),
	m_pMap(nullptr),
	m_iterator(),
	m_isActive(true),
	m_worldMatrix(CMatrix::Identity)
{
}

MapChip::~MapChip()
{
}

void MapChip::Init(const CVector3& position, const CQuaternion& rotation, const wchar_t* modelName, CAnimation* anim)
{
	//ライトの設定
	//float ambientLightColor = 0.4f;
	//float diffuseLightColor0 = 0.3f;
	//float diffuseLightColor1 = 0.3f;
	//float diffuseLightColor2 = 0.2f;
	//float diffuseLightColor3 = 0.15f;
	//m_light.SetAmbiemtLight({ ambientLightColor, ambientLightColor, ambientLightColor, 1.0f });
	//m_light.SetDiffuseLightColor(0, D3DXVECTOR4(diffuseLightColor0, diffuseLightColor0, diffuseLightColor0, 1.0f));
	//m_light.SetDiffuseLightColor(1, D3DXVECTOR4(diffuseLightColor1, diffuseLightColor1, diffuseLightColor1, 1.0f));
	//m_light.SetDiffuseLightColor(2, D3DXVECTOR4(diffuseLightColor2, diffuseLightColor2, diffuseLightColor2, 1.0f));
	//m_light.SetDiffuseLightColor(3, D3DXVECTOR4(diffuseLightColor3, diffuseLightColor3, diffuseLightColor3, 1.0f));
	//D3DXVECTOR3 lightDirection;
	//lightDirection = { -10.0f, -7.0f, -3.0f };
	//D3DXVec3Normalize(&lightDirection, &lightDirection);
	//m_light.SetDiffuseLightDirection(0, D3DXVECTOR4(lightDirection.x, lightDirection.y, lightDirection.z, 1.0f));
	//lightDirection = { 2.0f, -3.0f, 10.0f };
	//D3DXVec3Normalize(&lightDirection, &lightDirection);
	//m_light.SetDiffuseLightDirection(1, D3DXVECTOR4(lightDirection.x, lightDirection.y, lightDirection.z, 1.0f));
	//lightDirection = { -10.0f, -3.0f, 0.0f };
	//D3DXVec3Normalize(&lightDirection, &lightDirection);
	//m_light.SetDiffuseLightDirection(2, D3DXVECTOR4(lightDirection.x, lightDirection.y, lightDirection.z, 1.0f));
	//lightDirection = { 5.0f, 5.0f, 5.0f };
	//D3DXVec3Normalize(&lightDirection, &lightDirection);
	//m_light.SetDiffuseLightDirection(3, D3DXVECTOR4(lightDirection.x, lightDirection.y, lightDirection.z, 1.0f));

	//モデルの読み込み
	wchar_t filePath[64];
	swprintf(filePath, L"Assets/modelData/%s.cmo", modelName);
	//GetModelDataResource().Load(&m_skinModelData, anim, filePath);
	m_skinModel.Load(filePath);
	//m_skinModel.SetLight(&m_light);

	m_position = position;
	m_rotation = rotation;
	m_scale = { 1.0f, 1.0f, 1.0f };
	//m_skinModel.SetShadowCasterFlg(true);
	//m_skinModel.SetShadowReceiverFlg(true);
	////基本的に動かさないのでワールド行列を最初の一回だけ更新しておく。
	//m_skinModel.Update(m_position, m_rotation, m_scale);
	//m_skinModel.SetShadowCompesationFlg(true);
}

void MapChip::SetIterator(Map* map, std::list<MapChip*>::iterator iterator)
{
	m_pMap = map;
	m_iterator = iterator;
}

void MapChip::MapChipDelete()
{
	m_pMap->MapChipErase(m_iterator);
}

bool MapChip::Start()
{
	return true;
}

void MapChip::Update()
{
	//影を描画するのでシャドウマップに登録
	//m_skinModel.ShadowMapEntry();
}

void MapChip::Draw()
{
	//const Camera& camera = GetGameScene().GetCamera();
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}