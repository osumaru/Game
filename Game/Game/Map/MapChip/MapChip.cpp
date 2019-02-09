#include "stdafx.h"
#include "MapChip.h"
#include "../../Camera/GameCamera.h"

MapChip::MapChip():
	m_position(0.0f, 0.0f, 0.0f),
	m_rotation(0.0f, 0.0f, 0.0f, 1.0f),
	m_scale(1.0f, 1.0f, 1.0f),
	m_pMap(nullptr),
	m_iterator(),
	m_isActive(true),
	m_worldMatrix(CMatrix::Identity)
{
	this->SetIsActive(false);
}

MapChip::~MapChip()
{
}

void MapChip::Init(const CVector3& position, const CQuaternion& rotation, const wchar_t* modelName, CAnimation* anim)
{
	//ƒ‚ƒfƒ‹‚Ì“Ç‚Ýž‚Ý
	wchar_t filePath[64];
	swprintf(filePath, L"Assets/modelData/%s.cmo", modelName);
	m_skinModel.Load(filePath);

	m_position = position;
	m_rotation = rotation;
	m_scale = { 1.0f, 1.0f, 1.0f };

	m_skinModel.SetIsShadowReceiver(true);
	this->SetIsActive(true);
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
	//‰e‚ð•`‰æ‚·‚é‚Ì‚ÅƒVƒƒƒhƒEƒ}ƒbƒv‚É“o˜^
	m_skinModel.ShadowMapEntry();
}

void MapChip::Draw()
{
	if (&GetGameCamera() == nullptr) { return; }
	//const Camera& camera = GetGameScene().GetCamera();
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}