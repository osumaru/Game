#include "stdafx.h"
#include "WeaponManager.h"
#include "../Player.h"
#include "../../Camera/GameCamera.h"
#include "../../UI/Menu/EquipInventory.h"
#include "../Weapon/IWeapon.h"
#include "../Weapon/Bow.h"
#include "../Weapon/LongSword.h"
#include "../Weapon/TwinSword.h"
#include "../Weapon/Sword.h"
#include "../../Item/InventoryItem/InventorySword.h"
#include "../../Item/InventoryItem/InventoryLargeSword.h"
#include "../../Item/InventoryItem/InventoryBow.h"
#include "../../Item/InventoryItem/InventoryTwinSword.h"
#include "../../Scene/SceneManager.h"

std::unique_ptr<IInventoryEquip> CWeaponManager::m_equipWeapon[enWeaponNum];

void CWeaponManager::Init(CPlayer* player)
{
	int maxVertexBufferCount = 0;
	if (GetSceneManager().GetIsStart())
	{
		//毎回初期化する変数
		m_isAttack = false;
		m_isAttackCheck = false;
		m_isTraceDraw = false;

		for (int i = 0; i < enWeaponNum; i++)
		{
			std::unique_ptr<IWeapon> ptr;
			switch (i)
			{
			case enWeaponLongSword:
				ptr = std::make_unique<CLongSword>();
				break;
			case enWeaponTwinSword:
				ptr = std::make_unique<CTwinSword>();
				break;
			case enWeaponArrow:
				ptr = std::make_unique<CBow>();
				break;
			case enWeaponSword:
				ptr = std::make_unique<CSword>();
				break;
			}

			m_weapons[i] = std::move(ptr);
			m_weapons[i]->Init(player);
			
		}
		for (int i = 0; i < 2; i++)
		{
			m_weaponTrace[i].Init();
		}
	}
	else
	{
		for (int i = 0; i < enWeaponNum; i++)
		{
			std::unique_ptr<IWeapon> ptr;
			std::unique_ptr<IInventoryEquip> equipPtr;
			SWeaponStatus weaponStatus;
			wchar_t* itemName;
			wchar_t* textureFileName;
			switch (i)
			{
			case enWeaponLongSword:
				ptr = std::make_unique<CLongSword>();
				equipPtr = std::make_unique<CInventoryLargeSword>();
				weaponStatus.attack = 20;
				weaponStatus.weaponNum = EnPlayerWeapon::enWeaponLongSword;
				itemName = L"錆びた大剣";
				textureFileName = L"Assets/sprite/item/Equip/Equip_2.png";
				break;
			case enWeaponTwinSword:
				ptr = std::make_unique<CTwinSword>();
				equipPtr = std::make_unique<CInventoryTwinSword>();
				weaponStatus.attack = 5;
				weaponStatus.weaponNum = EnPlayerWeapon::enWeaponTwinSword;
				itemName = L"錆びた双剣";
				textureFileName = L"Assets/sprite/item/Equip/Equip_2.png";
				break;
			case enWeaponArrow:
				ptr = std::make_unique<CBow>();
				equipPtr = std::make_unique<CInventoryBow>();
				weaponStatus.attack = 1;
				weaponStatus.weaponNum = EnPlayerWeapon::enWeaponArrow;
				itemName = L"錆びた弓";
				textureFileName = L"Assets/sprite/item/Equip/Equip_2.png";
				break;
			case enWeaponSword:
				ptr = std::make_unique<CSword>();
				equipPtr = std::make_unique<CInventorySword>();
				weaponStatus.attack = 10;
				weaponStatus.weaponNum = EnPlayerWeapon::enWeaponSword;
				itemName = L"錆びた剣";
				textureFileName = L"Assets/sprite/item/Equip/Equip_2.png";
				break;
			}
			m_weapons[i] = std::move(ptr);
			m_weapons[i]->Init(player);
			m_equipWeapon[i] = std::move(equipPtr);
			m_equipWeapon[i]->Init(itemName, textureFileName);
			m_equipWeapon[i]->SetEquipStatus(weaponStatus);
		}
		for (int i = 0; i < 2; i++)
		{
			m_weaponTrace[i].Init();
		}
	}

	for (int i = 0; i < enWeaponNum; i++) 
	{
		//武器の頂点バッファの数を取得
		int vertexBufferCount = m_weapons[i]->GetVertexBufferCount();
		//双剣の場合
		if (i == enWeaponTwinSword)
		{
			//2つ目のモデルの頂点バッファの数を追加
			vertexBufferCount += dynamic_cast<CTwinSword*>(GetWeapon(enWeaponTwinSword))->GetTwinVertexBufferCount();
		}
		//全ての武器の中で一番多い頂点バッファの数を求める
		if (maxVertexBufferCount < vertexBufferCount)
		{
			maxVertexBufferCount = vertexBufferCount;
		}
	}
	//パーティクルの初期化
	SParticleEmittInfo particleInfo;
	particleInfo.filePath = L"Assets/particle/weaponLight.png";
	particleInfo.width = 0.15f;
	particleInfo.height = 0.15f;
	particleInfo.uv = { 0.0f,0.0f,1.0f,1.0f };
	particleInfo.randomPosition = { 0.0f, 0.0f, 0.0f };
	particleInfo.gravity = { 0.0f, 0.0f, 0.0f };
	particleInfo.lifeTime = 0.0f;
	particleInfo.emittIntervalTime = 2.0f;
	particleInfo.emitterLifeTime = 1.0f;
	particleInfo.emitterPosition = { 0.0f,0.0f,0.0f };
	particleInfo.moveSpeed = { 0.0f, 0.1f, 0.0f };
	particleInfo.randomMoveSpeed = { 0.0f, 0.0f, 0.0f };
	particleInfo.particleNum = 1;
	particleInfo.isFirstTimeRandom = false;
	particleInfo.alphaBlendState = enAlphaBlendStateAdd;
	for (int i = 0; i < maxVertexBufferCount; i++)
	{
		CParticle* particle = New<CParticle>(PRIORITY_UI);
		particle->Init(particleInfo, &GetGameCamera().GetCamera());
		particle->SetIsActive(false);
		particle->SetAlpha(PARTICLE_ALPHA);
		m_particleList.push_back(particle);
	}
}


void CWeaponManager::Update()
{
	if (!m_isAttack && GetPlayer().GetIsAction()) 
	{
		if (Pad().IsTriggerButton(enButtonUp))
		{
			const float ChangeVolume = 0.3f;
			CSoundSource* ChangeSound = New<CSoundSource>(0);
			ChangeSound->Init("Assets/sound/SystemSound/EquipOff.wav");
			ChangeSound->Play(false);
			ChangeSound->SetVolume(ChangeVolume);
			m_weaponState = enWeaponSword;
		}
		else if (Pad().IsTriggerButton(enButtonDown))
		{
			const float ChangeVolume = 0.1f;
			CSoundSource* ChangeSound = New<CSoundSource>(0);
			ChangeSound->Init("Assets/sound/SystemSound/EquipOff.wav");
			ChangeSound->Play(false);
			ChangeSound->SetVolume(ChangeVolume);
			m_weaponState = enWeaponArrow;
		}
		else if (Pad().IsTriggerButton(enButtonLeft))
		{
			const float ChangeVolume = 0.1f;
			CSoundSource* ChangeSound = New<CSoundSource>(0);
			ChangeSound->Init("Assets/sound/SystemSound/EquipOff.wav");
			ChangeSound->Play(false);
			ChangeSound->SetVolume(ChangeVolume);
			m_weaponState = enWeaponTwinSword;
		}
		else if (Pad().IsTriggerButton(enButtonRight))
		{
			const float ChangeVolume = 0.1f;
			CSoundSource* ChangeSound = New<CSoundSource>(0);
			ChangeSound->Init("Assets/sound/SystemSound/EquipOff.wav");
			ChangeSound->Play(false);
			ChangeSound->SetVolume(ChangeVolume);
			m_weaponState = enWeaponLongSword;
		}
	}

	if (m_particleDraw)
	{
		m_particleTimer += GameTime().GetDeltaFrameTime();
		if (m_particleTimer > PARTICLE_TIME)
		{
			for (auto& particle : m_particleList)
			{
				particle->SetIsActive(false);
			}
			m_particleDraw = false;
		}
		else
		{
			for (auto& particle : m_particleList)
			{
				if (particle->IsActive())
				{
					particle->SetAlpha(PARTICLE_ALPHA * (1.0f - m_particleTimer / PARTICLE_TIME));
				}
			}
		}
	}

	//武器を出し続けるか
	if (m_drawingWeapon && !m_isAttack)
	{
		m_drawingWeaponTimer += GameTime().GetDeltaFrameTime();
		if (m_drawingWeaponTimer > DRAWING_WEAPON_TIME)
		{
			//パーティクルを出す
			ParticleSetting();
			m_drawingWeapon = false;
			m_drawingWeaponTimer = 0.0f;
		}
	}

	m_weapons[m_weaponState]->Updater();
}

void CWeaponManager::Draw()
{

	m_weapons[m_weaponState]->Drawer();
}

void CWeaponManager::AfterDraw()
{
	if (m_isAttack && m_isTraceDraw)
	{
		for (int i = 0; i < GetWeapon()->GetMaxWeaponHitNum();i++)
		{
			m_weaponTrace[i].Draw();
		}
	}
	m_weapons[m_weaponState]->AfterDrawer();
}

void CWeaponManager::ParticleSetting()
{
	//タイマーを初期化
	m_particleTimer = 0.0f;
	//パーティクル描画フラグを立てる
	m_particleDraw = true;
	//武器の頂点バッファの座標を格納しているリストを取得
	const std::vector<CVector3> vertexBufferList = m_weapons[m_weaponState]->GetVertexBufferList();
	std::vector<CVector3>::const_iterator it = vertexBufferList.begin();
	//武器モデルのワールド行列を取得
	const CMatrix worldMatrix = m_weapons[m_weaponState]->GetSkinModel().GetWorldMatrix();
	for (auto& particle : m_particleList)
	{
		//頂点バッファの数だけパーティクルを更新したか
		if (it == vertexBufferList.end())
		{
			break;
		}
		CVector3 position = *it;
		position.Mul(worldMatrix);
		particle->SetAlpha(PARTICLE_ALPHA);
		particle->SetPosition(position);
		particle->SetIsActive(true);
		particle->UpdateWorldMatrix();
		it++;
	}
	//双剣の場合は２つ目のモデルの分も行う
	if (m_weaponState == enWeaponTwinSword)
	{
		const CTwinSword* twinSword = dynamic_cast<const CTwinSword*>(GetWeapon(enWeaponTwinSword));
		//武器の頂点バッファの座標を格納しているリストを取得
		const std::vector<CVector3> twinVertexBufferList = twinSword->GetTwinVertexBufferList();
		std::vector<CVector3>::const_iterator it = twinVertexBufferList.begin();
		//武器モデルのワールド行列を取得
		const CMatrix worldMatrix = twinSword->GetSkinModel().GetWorldMatrix();
		int count = 0;
		for (auto& particle : m_particleList)
		{
			//頂点バッファの数だけパーティクルを更新したか
			if (it == twinVertexBufferList.end())
			{
				break;
			}
			//1つ目のモデルの分は何もしない
			if (count < vertexBufferList.size())
			{
				count++;
				continue;
			}
			CVector3 position = *it;
			position.Mul(worldMatrix);
			particle->SetAlpha(PARTICLE_ALPHA);
			particle->SetPosition(position);
			particle->SetIsActive(true);
			particle->UpdateWorldMatrix();
			it++;
		}
	}
}

void CWeaponManager::ChangeEquipWeapon(std::unique_ptr<IInventoryEquip> equipWeapon, EnPlayerWeapon weaponNum)
{
	//現在装備中の武器を一時的に保存する
	std::unique_ptr<IInventoryEquip> changeEquip = std::move(m_equipWeapon[weaponNum]);
	//変更したい武器を装備中の武器に設定する
	m_equipWeapon[weaponNum] = std::move(equipWeapon);
	//保存していた武器をインベントリに追加する
	CEquipInventory::AddEquipList(std::move(changeEquip));
}
