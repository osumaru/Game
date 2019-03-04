#include "stdafx.h"
#include "MapChip.h"
#include "../../Camera/GameCamera.h"

MapChip::MapChip():
	m_position(0.0f, 0.0f, 0.0f),
	m_rotation(0.0f, 0.0f, 0.0f, 1.0f),
	m_scale(1.0f, 1.0f, 1.0f),
	m_pMap(nullptr),
	m_iterator()
{
	this->SetIsActive(false);
}

MapChip::~MapChip()
{
}

void MapChip::Init(const SMapChipInfo& info, CAnimation* anim)
{
	m_initializeInfo = info;
	//ƒ‚ƒfƒ‹‚Ì“Ç‚Ýž‚Ý
	wchar_t filePath[64];
	swprintf(filePath, L"Assets/modelData/%s.cmo", info.m_modelName);
	m_skinModel.Load(filePath, anim);

	m_position = info.m_position;
	m_rotation = info.m_rotation;
	m_scale = { 1.0f, 1.0f, 1.0f };

	m_skinModel.SetIsShadowCaster(true);
	this->SetIsActive(true);

}

void MapChip::SetIterator(Map* map, std::list<MapChip*>::iterator iterator, int areaX, int areaY)
{
	m_pMap = map;
	m_iterator = iterator;
	m_areaX = areaX;
	m_areaY = areaY;
}

void MapChip::MapChipDelete()
{
	m_pMap->MapChipErase(m_iterator, m_areaX, m_areaY);
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