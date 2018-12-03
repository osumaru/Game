#include "stdafx.h"
#include "EquipInventory.h"
#include "Menu.h"
#include "../../Player/Player.h"
#include "../../Item/IItem.h"
#include "../../Player/Weapon/WeaponManager.h"

std::list<SWeaponStatus> CEquipInventory::m_equipList;

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
	CTexture* texture = TextureResource().LoadTexture(L"Assets/sprite/MenuUI/Back_Menu.png");
	m_background.Init(texture);
	//AボタンとBボタン表示の初期化
	texture = TextureResource().LoadTexture(L"Assets/sprite/statusWindow.png");
	m_buttonBackground.Init(texture);
	m_buttonBackground.SetSize({ 1280.0f, 60.0f });
	m_buttonBackground.SetPosition({ 0.0f, -330.0f });
	m_buttonBackground.SetAlpha(0.3f);
	texture = TextureResource().LoadTexture(L"Assets/sprite/ButtonA.png");
	m_buttonA.Init(texture);
	m_buttonA.SetSize({ 35.0f,35.0f });
	m_buttonA.SetPosition({ 200.0f, -330.0f });
	texture = TextureResource().LoadTexture(L"Assets/sprite/ButtonB.png");
	m_buttonB.Init(texture);
	m_buttonB.SetSize({ 35.0f,35.0f });
	m_buttonB.SetPosition({ 325.0f, -330.0f });
	texture = TextureResource().LoadTexture(L"Assets/sprite/ButtonY.png");
	m_buttonY.Init(texture);
	m_buttonY.SetSize({ 35.0f,35.0f });
	m_buttonY.SetPosition({ 450.0f, -330.0f });
	//ボタンフォントの初期化
	m_buttonAFont.Init(L"装備する");
	m_buttonAFont.SetSize({ 0.5f, 0.5f });
	m_buttonAFont.SetPosition({ 212.5f, -319.0f });
	m_buttonBFont.Init(L"戻る");
	m_buttonBFont.SetSize({ 0.5f, 0.5f });
	m_buttonBFont.SetPosition({ 342.5f, -319.0f });
	m_buttonYFont.Init(L"捨てる");
	m_buttonYFont.SetSize({ 0.5f, 0.5f });
	m_buttonYFont.SetPosition({ 472.5f, -319.0f });
	//ステータスウィンドウの背景を初期化
	for (int i = 0; i < enFont_StatusNum; i++) 
	{
		texture = TextureResource().LoadTexture(L"Assets/sprite/statusWindow.png");
		m_statusWindow[i].Init(texture);
		m_statusWindow[i].SetSize({ 320.0f, 450.0f });
		m_statusWindow[i].SetAlpha(0.3f);
	}
	m_statusWindow[enFont_CurrentStatus].SetPosition({ 70.0f, 80.0f });
	m_statusWindow[enFont_ChangeStatus].SetPosition({ 470.0f, 80.0f });
	//右矢印の初期化
	texture = TextureResource().LoadTexture(L"Assets/sprite/right.png");
	m_right.Init(texture);
	m_right.SetSize({ 80.0f, 80.0f });
	m_right.SetPosition({ 270.0f, 80.0f });
	//カーソルを初期化
	texture = TextureResource().LoadTexture(L"Assets/sprite/Pointer.png");
	m_pointer.Init(texture);
	m_pointer.SetPosition(m_basePos);
	m_pointer.SetSize(m_baseSize);
	//装備武器のアイコンを初期化
	texture = TextureResource().LoadTexture(L"Assets/sprite/sword.png");
	m_equipWeapon[enWeaponSword].Init(texture);
	m_equipWeapon[enWeaponSword].SetSize({ 65.0f,65.0f });
	m_equipWeapon[enWeaponSword].SetPosition({ -360.0f, -120.0f });
	texture = TextureResource().LoadTexture(L"Assets/sprite/largeSword.png");
	m_equipWeapon[enWeaponLongSword].Init(texture);
	m_equipWeapon[enWeaponLongSword].SetSize({ 65.0f,65.0f });
	m_equipWeapon[enWeaponLongSword].SetPosition({ -290.0f, -190.0f });
	texture = TextureResource().LoadTexture(L"Assets/sprite/bow.png");
	m_equipWeapon[enWeaponArrow].Init(texture);
	m_equipWeapon[enWeaponArrow].SetSize({ 65.0f,65.0f });
	m_equipWeapon[enWeaponArrow].SetPosition({ -360.0f, -260.0f });
	texture = TextureResource().LoadTexture(L"Assets/sprite/twinSword.png");
	m_equipWeapon[enWeaponTwinSword].Init(texture);
	m_equipWeapon[enWeaponTwinSword].SetSize({ 65.0f,65.0f });
	m_equipWeapon[enWeaponTwinSword].SetPosition({ -430.0f, -190.0f });
	for (int i = 0; i < enWeaponNum; i++)
	{
		IWeapon* weapon = GetPlayer().GetWeaponManager().GetWeapon((EnPlayerWeapon)i);
		if (weapon->GetWeaponStatus().weaponNum == enInvalid) 
		{
			//装備がなければ描画しない
			m_equipWeapon[i].SetIsDraw(false);
		}
		//装備武器アイコンの枠の初期化
		texture = TextureResource().LoadTexture(L"Assets/sprite/EquipFrame.png");
		m_equipFrame[i].Init(texture);
		m_equipFrame[i].SetSize({ 70.0f,70.0f });
		m_equipFrame[i].SetPosition(m_equipWeapon[i].GetPosition());
	}
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
					fontPos.x + (m_right.GetSize().x + m_statusWindow[enFont_CurrentStatus].GetSize().x) * j,
					fontPos.y - m_baseSize.y * i
			});
			CVector2 fontSize = { 0.7f, 0.7f };
			m_statusFont[j][i].SetSize(fontSize);
		}
	}
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

	if (Pad().IsTriggerButton(enButtonA)) 
	{
		//装備する
		Equip();
	}

	if (Pad().IsTriggerButton(enButtonY))
	{
		//アイテムを捨てる
		Erase();
	}

	//ステータス計算
	CalucStatus();

	if (Pad().IsTriggerButton(enButtonB)) 
	{
		//メニューに戻る
		m_menu->SetIsActive(true);
		Delete(this);
	}
}

void CEquipInventory::AfterDraw()
{
	m_background.Draw();
	for (int i = 0; i < m_equipList.size(); i++)
	{
		m_equip[i].Draw();
	}
	for (int i = 0; i < enWeaponNum; i++)
	{
		m_equipFrame[i].Draw();
		m_equipWeapon[i].Draw();
	}
	m_pointer.Draw();
	for (int i = 0; i < enFont_StatusNum; i++)
	{
		m_statusWindow[i].Draw();
	}
	m_right.Draw();
	m_buttonBackground.Draw();
	m_buttonA.Draw();
	m_buttonB.Draw();
	m_buttonY.Draw();
	for (int j = 0; j < enFont_StatusNum; j++)
	{
		for (int i = 0; i < enStatus_Num; i++)
		{
			m_statusFont[j][i].Draw();
		}
	}
	m_buttonAFont.Draw();
	m_buttonBFont.Draw();
	m_buttonYFont.Draw();
}

void CEquipInventory::EquipListReset(bool isInit)
{
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
	if (m_pointerNum >= equipNum || m_equipList.empty()) {
		//選んだ場所の装備がリストの中にない又はリストが空になっている
		return;
	}
	//選んだ武器のアイコンを描画させる
	std::list<SWeaponStatus>::iterator it;
	it = m_equipList.begin();
	for (int i = 0; i < m_pointerNum; i++)
	{
		it++;
	}
	EnPlayerWeapon weaponNumber = (*it).weaponNum;
	m_equipWeapon[weaponNumber].SetIsDraw(true);
	//選んだ装備と現在の装備を交換する
	IWeapon* weapon = GetPlayer().GetWeaponManager().GetWeapon(weaponNumber);
	if (weapon->GetWeaponStatus().weaponNum == enInvalid)
	{
		//何も装備していない
		weapon->SetWeaponStatus(*it);
		m_equipList.erase(it);
	}
	else
	{
		//装備を交換する
		SWeaponStatus equipWeapon = weapon->GetWeaponStatus();
		weapon->SetWeaponStatus(*it);
		(*it) = equipWeapon;
	}
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

	std::list<SWeaponStatus>::iterator it;
	it = m_equipList.begin();
	SWeaponStatus equipStatus;
	if (weaponStatus.weaponNum != EnPlayerWeapon::enInvalid)
	{
		//現在の装備のステータスを取得
		equipStatus = GetPlayer().GetWeaponManager().GetWeaponStatus(weaponStatus.weaponNum);
	}

	//装備変更した場合のステータスを計算する
	wchar_t font[256];
	for (int j = 0; j < enFont_StatusNum; j++) 
	{
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

void CEquipInventory::Erase()
{
	//装備の数を取得
	size_t equipNum = m_equipList.size();
	if (m_pointerNum >= equipNum || m_equipList.empty()) {
		//選んだ場所の装備がリストの中にない又はリストが空になっている
		return;
	}
	//選んだ装備を捨てる
	std::list<SWeaponStatus>::iterator it;
	it = m_equipList.begin();
	for (int i = 0; i < m_pointerNum; i++)
	{
		it++;
	}
	m_equipList.erase(it);
	//装備リストを整理する
	EquipListReset(false);
}

void CEquipInventory::AddEquipList(SWeaponStatus& weaponStatus)
{
	if (m_equipList.size() < m_equipLimit)
	{
		//所持上限を超えていなければ装備リストに追加
		m_equipList.push_back(weaponStatus);
	}
}