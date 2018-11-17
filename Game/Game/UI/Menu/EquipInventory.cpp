#include "stdafx.h"
#include "EquipInventory.h"
#include "Menu.h"
#include "../../Player/Player.h"
#include "../../Item/IItem.h"
#include "../../Player/Weapon/WeaponManager.h"

CEquipInventory::CEquipInventory(){}

CEquipInventory::~CEquipInventory(){}

void CEquipInventory::Init(CMenu * menu)
{
	m_menu = menu;
	//インベントリの幅と高さを初期化
	m_width = 5;
	m_height = 3;
	//座標とサイズを初期化
	m_basePos = { -560.0f, 180.0f };
	m_baseSize = { 100.0f, 100.0f };
	//インベントリの背景を初期化
	m_backGroundTexture.Load(L"Assets/sprite/MenuUI/Back_Menu.png");
	m_backGround.Init(&m_backGroundTexture);
	m_statusWindowTexture.Load(L"Assets/sprite/statusWindow.png");
	m_statusWindow.Init(&m_statusWindowTexture);
	m_statusWindow.SetSize({ 320.0f, 450.0f });
	m_statusWindow.SetAlpha(0.3f);
	m_rightTexture.Load(L"Assets/sprite/right.png");
	m_right.Init(&m_rightTexture);
	m_right.SetSize(m_baseSize);
	//カーソルを初期化
	m_pointerTexture.Load(L"Assets/sprite/Pointer.png");
	m_pointer.Init(&m_pointerTexture);
	m_pointer.SetPosition(m_basePos);
	m_pointer.SetSize(m_baseSize);
	//装備リストを取得
	m_equipList = GetPlayer().GetWeaponManager().GetEquipList();
	m_width = 5;
	m_height = 1;
	if (!m_equipList.empty()) {
		//リストにアイテムがある
		int idx = 0;
		for (auto& equip : m_equipList)
		{
			//アイテムの種類を取得
			EnPlayerWeapon weaponNum = equip.weaponNum;
			if (weaponNum == enWeaponSword)
			{
				//剣
				CTexture* itemTexure = TextureResource().LoadTexture(L"Assets/sprite/sword.png");
				m_equip[idx].Init(itemTexure);
			}
			else if (weaponNum == enWeaponLongSword)
			{
				//大剣
				CTexture* itemTexure = TextureResource().LoadTexture(L"Assets/sprite/largeSword.png");
				m_equip[idx].Init(itemTexure);
			}
			else if (weaponNum == enWeaponArrow)
			{
				//弓
				CTexture* itemTexure = TextureResource().LoadTexture(L"Assets/sprite/bow.png");
				m_equip[idx].Init(itemTexure);
			}
			else if (weaponNum == enWeaponTwinSword)
			{
				//双剣
				CTexture* itemTexure = TextureResource().LoadTexture(L"Assets/sprite/twinSword.png");
				m_equip[idx].Init(itemTexure);
			}
			//座標とサイズを決める
			CVector2 position = m_basePos;
			position.x += m_baseSize.x * (idx % m_width);
			position.y -= m_baseSize.y * (idx / m_width);
			if (idx != 0 && idx % m_width == 0)
			{
				//インベントリの幅を超えたら行を下げる
				m_height++;
			}
			m_equip[idx].SetPosition(position);
			m_equip[idx].SetSize(m_baseSize);
			idx++;
		}
	}
	m_pointer.SetSize(m_baseSize);
	//装備リストを整理する
	EquipListReset(true);
	//ステータス表示を初期化
	SplayerStatus playerStatus = GetPlayer().GetStatus();
	CVector2 fontPos = { m_basePos.x + m_baseSize.x * m_width, m_basePos.y };
	wchar_t font[256];
	for (int j = 0; j < enFont_StatusNum; j++)
	{
		for (int i = 0; i < enStatus_Num; i++)
		{
			switch (i)
			{
			case enStatus_Hp:
				swprintf(font, L"最大HP : %d", playerStatus.MaxHealth);
				break;
			case enStatus_Attack:
				swprintf(font, L"攻撃力 : %d", playerStatus.Strength);
				break;
			case enStatus_Defense:
				swprintf(font, L"防御力 : %d", playerStatus.Defense);
				break;
			}
			m_statusFont[j][i].Init(font);
			m_statusFont[j][i].SetPosition({
					fontPos.x + (m_right.GetSize().x + m_statusWindow.GetSize().x) * j,
					fontPos.y - m_baseSize.y * i
			});
			CVector2 fontSize = { 0.7f, 0.7f };
			m_statusFont[j][i].SetSize(fontSize);
		}
	}
	CVector2 statusWindowPos = { m_basePos.x + m_baseSize.x * m_width, m_basePos.y };
	statusWindowPos.x += m_statusWindow.GetSize().x / 2.0f - 30.0f;
	statusWindowPos.y -= m_baseSize.y;
	m_statusWindow.SetPosition(statusWindowPos);
	CVector2 rightPos = statusWindowPos;
	rightPos.x += m_statusWindow.GetSize().x / 2.0f + m_right.GetSize().x / 2.0f;
	m_right.SetPosition(rightPos);
}

bool CEquipInventory::Start()
{
	m_menu->SetIsActive(false);
	return true;
}

void CEquipInventory::Update()
{
	//カーソル移動
	PointerMove();

	//装備する
	Equip();

	//ステータス計算
	CalucStatus();

	if (Pad().IsTriggerButton(enButtonB)) {
		//メニューに戻る
		m_menu->SetIsActive(true);
		Delete(this);
	}
}

void CEquipInventory::AfterDraw()
{
	m_backGround.Draw();
	for (int i = 0; i < m_equipList.size(); i++) {
		m_equip[i].Draw();
	}
	m_pointer.Draw();
	m_statusWindow.Draw();
	m_right.Draw();
	for (int j = 0; j < enFont_StatusNum; j++) {
		for (int i = 0; i < enStatus_Num; i++) {
			m_statusFont[j][i].Draw();
		}
	}
}

void CEquipInventory::EquipListReset(bool isInit)
{
	m_equipList = GetPlayer().GetWeaponManager().GetEquipList();
	if (m_equipList.empty()) 
	{
		//装備が何もない
		return;
	}
	int idx = 0;
	for (auto& equip : m_equipList)
	{
		//装備の種類を取得
		EnPlayerWeapon weaponNum = equip.weaponNum;
		CTexture* equipTexture = nullptr;
		if (weaponNum == enWeaponSword)
		{
			//剣
			equipTexture = TextureResource().LoadTexture(L"Assets/sprite/sword.png");
		}
		else if (weaponNum == enWeaponLongSword)
		{
			//大剣
			equipTexture = TextureResource().LoadTexture(L"Assets/sprite/largeSword.png");
		}
		else if (weaponNum == enWeaponArrow)
		{
			//弓
			equipTexture = TextureResource().LoadTexture(L"Assets/sprite/bow.png");
		}
		else if (weaponNum == enWeaponTwinSword)
		{
			//双剣
			equipTexture = TextureResource().LoadTexture(L"Assets/sprite/twinSword.png");
		}
		if (isInit) {
			//初期化する
			m_equip[idx].Init(equipTexture);
		}
		else {
			//テクスチャを設定する
			m_equip[idx].SetTexture(equipTexture);
		}
		//座標とサイズを決める
		CVector2 position = m_basePos;
		position.x += m_baseSize.x * (idx % m_width);
		position.y -= m_baseSize.y * (idx / m_width);
		m_equip[idx].SetPosition(position);
		m_equip[idx].SetSize(m_baseSize);
		idx++;
	}
}

void CEquipInventory::PointerMove()
{
	CVector2 position = m_pointer.GetPosition();
	int number = m_pointerNum;
	if (Pad().IsTriggerButton(enButtonRight))
	{
		//右にカーソルを動かす
		position.x += m_baseSize.x;
		number++;
		if (position.x >= m_basePos.x + m_baseSize.x * m_width)
		{
			//右端だった場合はそのまま
			position.x = m_basePos.x + m_baseSize.x * (m_width - 1);
		}
		else
		{
			//動いたらカーソルで選んでいる番号を更新
			m_pointerNum = number;
		}
	}
	else if (Pad().IsTriggerButton(enButtonLeft))
	{
		//左にカーソルを動かす
		position.x -= m_baseSize.x;
		number--;
		if (position.x <= m_basePos.x - m_baseSize.x)
		{
			//左端だった場合はそのまま
			position.x = m_basePos.x;
		}
		else
		{
			//動いたらカーソルで選んでいる番号を更新
			m_pointerNum = number;
		}
	}
	else if (Pad().IsTriggerButton(enButtonUp))
	{
		//上にカーソルを動かす
		position.y += m_baseSize.y;
		number -= m_width;
		if (position.y >= m_basePos.y + m_baseSize.y)
		{
			//上端だった場合はそのまま
			position.y = m_basePos.y;
		}
		else
		{
			//動いたらカーソルで選んでいる番号を更新
			m_pointerNum = number;
		}
	}
	else if (Pad().IsTriggerButton(enButtonDown))
	{
		//下にカーソルを動かす
		position.y -= m_baseSize.y;
		number += m_width;
		if (position.y <= m_basePos.y - m_baseSize.y * m_height)
		{
			//下端だった場合はそのまま
			position.y = m_basePos.y - m_baseSize.y * (m_height - 1);
		}
		else
		{
			//動いたらカーソルで選んでいる番号を更新
			m_pointerNum = number;
		}
	}
	//座標を更新
	m_pointer.SetPosition(position);
}

void CEquipInventory::Equip()
{
	//装備の数を取得
	size_t equipNum = m_equipList.size();
	if (m_pointerNum >= equipNum || !Pad().IsTriggerButton(enButtonA)) {
		return;
	}
	//カーソルで選んでいる装備をつける
	GetPlayer().GetWeaponManager().ChangeEquip(m_pointerNum);
	m_equipList = GetPlayer().GetWeaponManager().GetEquipList();
	m_width = 5;
	m_height = 1;
	if (!m_equipList.empty()) {
		//リストにアイテムがある
		int idx = 0;
		for (auto& equip : m_equipList)
		{
			//アイテムの種類を取得
			EnPlayerWeapon weaponNum = equip.weaponNum;
			if (weaponNum == enWeaponSword)
			{
				//剣
				CTexture* itemTexure = TextureResource().LoadTexture(L"Assets/sprite/sword.png");
				m_equip[idx].SetTexture(itemTexure);
			}
			else if (weaponNum == enWeaponLongSword)
			{
				//大剣
				CTexture* itemTexure = TextureResource().LoadTexture(L"Assets/sprite/largeSword.png");
				m_equip[idx].SetTexture(itemTexure);
			}
			else if (weaponNum == enWeaponArrow)
			{
				//弓
				CTexture* itemTexure = TextureResource().LoadTexture(L"Assets/sprite/bow.png");
				m_equip[idx].SetTexture(itemTexure);
			}
			else if (weaponNum == enWeaponTwinSword)
			{
				//双剣
				CTexture* itemTexure = TextureResource().LoadTexture(L"Assets/sprite/twinSword.png");
				m_equip[idx].SetTexture(itemTexure);
			}
			//座標とサイズを決める
			CVector2 position = m_basePos;
			position.x += m_baseSize.x * (idx % m_width);
			position.y -= m_baseSize.y * (idx / m_width);
			if (idx != 0 && idx % m_width == 0)
			{
				//インベントリの幅を超えたら行を下げる
				m_height++;
			}
			m_equip[idx].SetPosition(position);
			m_equip[idx].SetSize(m_baseSize);
			idx++;
		}
	}
	GetPlayer().GetWeaponManager().ChangeEquip(m_pointerNum);
	//装備リストを整理する
	EquipListReset(false);
}

void CEquipInventory::CalucStatus()
{
	//プレイヤーのステータスを取得
	SplayerStatus playerStatus = GetPlayer().GetStatus();
	//装備の数を取得
	size_t equipNum = m_equipList.size();
	SWeaponStatus weaponStatus;
	if (m_pointerNum < equipNum) {
		//所持している装備を選んでいる場合はその装備のステータスを取得
		std::list<SWeaponStatus>::iterator it;
		it = m_equipList.begin();
		for (int i = 0; i < m_pointerNum; i++)
		{
			it++;
		}
		weaponStatus = (*it);
	}

	//装備変更した場合のステータスを計算する
	std::list<SWeaponStatus>::iterator it;
	it = m_equipList.begin();
	for (int i = 0; i < m_pointerNum; i++)
	{
		SWeaponStatus equipStatus;
		if (weaponStatus.weaponNum != EnPlayerWeapon::enInvalid)
		{
			//現在の装備のステータスを取得
			equipStatus = GetPlayer().GetWeaponManager().GetWeaponStatus(weaponStatus.weaponNum);
		}

		//装備変更した場合のステータスを計算する
		wchar_t font[256];
		for (int j = 0; j < enFont_StatusNum; j++) {
			if (j == enFont_ChangeStatus)
			{
				equipStatus = weaponStatus;
			}
			for (int i = 0; i < enStatus_Num; i++)
			{
				int statusNum = 0;
				switch (i)
				{
				case enStatus_Hp:
					statusNum = playerStatus.MaxHealth;
					swprintf(font, L"最大HP : %d", statusNum);
					break;
				case enStatus_Attack:
					statusNum = equipStatus.attack + playerStatus.Strength;
					swprintf(font, L"攻撃力 : %d", statusNum);
					break;
				case enStatus_Defense:
					statusNum = equipStatus.diffence + playerStatus.Defense;
					swprintf(font, L"防御力 : %d", statusNum);
					break;
				}
				m_statusFont[j][i].SetString(font);
			}
		}
	}
}
