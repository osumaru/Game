#include "stdafx.h"
#include "EquipInventory.h"
#include "Menu.h"
#include "../../Player/Player.h"
#include "../../Item/IItem.h"
#include "../../Player/Weapon/WeaponManager.h"
#include "../../Item/InventoryItem/IInventoryEquip.h"

CEquipInventory::CEquipInventory(){}

CEquipInventory::~CEquipInventory(){}

void CEquipInventory::Init(CMenu * menu)
{
	m_menu = menu;
	//インベントリの幅と高さを初期化
	m_width = 5;
	m_height = CEquipList::m_equipLimit / m_width;
	//座標とサイズを初期化
	m_basePos = { -550.0f, 200.0f };
	m_baseSize = { 100.0f, 100.0f };
	//項目を初期化
	CTexture* texture = TextureResource().LoadTexture(L"Assets/sprite/Weapon.png");
	m_headline.Init(texture);
	m_headline.SetPosition({ -450.0f, 310.0f });
	m_headline.SetSize({ 300.0f, 75.0f });
	//インベントリの背景を初期化
	texture = TextureResource().LoadTexture(L"Assets/sprite/BackGround.png");
	m_background.Init(texture);
	m_background.SetPosition({ 0.0f, 30.0f });
	m_background.SetSize({ 1250.0f, 650.0f });
	//インベントリウィンドウを初期化
	texture = TextureResource().LoadTexture(L"Assets/sprite/InventoryWindow.png");
	m_inventoryWindow.Init(texture);
	m_inventoryWindow.SetPosition({ -350.0f, -10.0f });
	m_inventoryWindow.SetSize({530.0f, 560.0f});
	//インベントリの枠を初期化
	texture = TextureResource().LoadTexture(L"Assets/sprite/Frame.png");
	for (int i = 0; i < CEquipList::m_equipLimit; i++)
	{
		m_frame[i].Init(texture);
		m_frame[i].SetSize(m_baseSize);
		CVector2 position = m_basePos;
		position.x += m_baseSize.x * (i % m_width);
		position.y -= m_baseSize.y * (i / m_width);
		m_frame[i].SetPosition(position);
	}
	//ボタン表示の初期化
	texture = TextureResource().LoadTexture(L"Assets/sprite/ButtonBackGround.png");
	m_buttonBackground.Init(texture);
	m_buttonBackground.SetSize({ 1200.0f, 40.0f });
	m_buttonBackground.SetPosition({ 0.0f, -325.0f });
	m_buttonBackground.SetAlpha(0.8f);
	texture = TextureResource().LoadTexture(L"Assets/sprite/ButtonA.png");
	m_buttonA.Init(texture);
	m_buttonA.SetSize({ 30.0f,30.0f });
	m_buttonA.SetPosition({ 200.0f, -325.0f });
	texture = TextureResource().LoadTexture(L"Assets/sprite/ButtonB.png");
	m_buttonB.Init(texture);
	m_buttonB.SetSize({ 30.0f,30.0f });
	m_buttonB.SetPosition({ 330.0f, -325.0f });
	texture = TextureResource().LoadTexture(L"Assets/sprite/ButtonY.png");
	m_buttonY.Init(texture);
	m_buttonY.SetSize({ 30.0f,30.0f });
	m_buttonY.SetPosition({ 460.0f, -325.0f });
	//ボタン文字の初期化
	texture = TextureResource().LoadTexture(L"Assets/sprite/Equip.png");
	m_buttonAMoji.Init(texture);
	m_buttonAMoji.SetPosition({ 240.0f, -325.0f });
	m_buttonAMoji.SetSize({ 40.0f,20.0f });
	texture = TextureResource().LoadTexture(L"Assets/sprite/return.png");
	m_buttonBMoji.Init(texture);
	m_buttonBMoji.SetPosition({ 370.0f, -325.0f });
	m_buttonBMoji.SetSize({ 40.0f,20.0f });
	texture = TextureResource().LoadTexture(L"Assets/sprite/erase.png");
	m_buttonYMoji.Init(texture);
	m_buttonYMoji.SetPosition({ 510.0f, -325.0f });
	m_buttonYMoji.SetSize({ 60.0f,20.0f });
	//ステータスウィンドウの背景を初期化
	texture = TextureResource().LoadTexture(L"Assets/sprite/statusWindow.png");
	for (int i = 0; i < enFont_StatusNum; i++) 
	{
		m_statusWindow[i].Init(texture);
		m_statusWindow[i].SetSize({ 340.0f, 450.0f });
	}
	m_statusWindow[enFont_CurrentStatus].SetPosition({ 100.0f, 30.0f });
	m_statusWindow[enFont_ChangeStatus].SetPosition({ 440.0f, 30.0f });
	//右矢印の初期化
	texture = TextureResource().LoadTexture(L"Assets/sprite/right.png");
	m_right.Init(texture);
	m_right.SetSize({ 80.0f, 80.0f });
	m_right.SetPosition({ 270.0f, 30.0f });
	//カーソルを初期化
	texture = TextureResource().LoadTexture(L"Assets/sprite/Pointer.png");
	m_pointer.Init(texture);
	m_pointer.SetPosition(m_basePos);
	m_pointer.SetSize(m_baseSize);
	//装備武器のアイコンを初期化
	texture = TextureResource().LoadTexture(L"Assets/sprite/Item/Equip/Sword.png");
	m_equipWeapon[enWeaponSword].Init(texture);
	m_equipWeapon[enWeaponSword].SetSize({ 65.0f,65.0f });
	m_equipWeapon[enWeaponSword].SetPosition({ -350.0f, -100.0f });
	texture = TextureResource().LoadTexture(L"Assets/sprite/Item/Equip/LargeSword.png");
	m_equipWeapon[enWeaponLongSword].Init(texture);
	m_equipWeapon[enWeaponLongSword].SetSize({ 65.0f,65.0f });
	m_equipWeapon[enWeaponLongSword].SetPosition({ -280.0f, -170.0f });
	texture = TextureResource().LoadTexture(L"Assets/sprite/Item/Equip/Bow.png");
	m_equipWeapon[enWeaponArrow].Init(texture);
	m_equipWeapon[enWeaponArrow].SetSize({ 65.0f,65.0f });
	m_equipWeapon[enWeaponArrow].SetPosition({ -350.0f, -240.0f });
	texture = TextureResource().LoadTexture(L"Assets/sprite/Item/Equip/TwinSword.png");
	m_equipWeapon[enWeaponTwinSword].Init(texture);
	m_equipWeapon[enWeaponTwinSword].SetSize({ 65.0f,65.0f });
	m_equipWeapon[enWeaponTwinSword].SetPosition({ -420.0f, -170.0f });
	for (int i = 0; i < enWeaponNum; i++)
	{
		IInventoryEquip* weapon = GetPlayer().GetWeaponManager().GetEquipWeapon((EnPlayerWeapon)i);
		if (weapon->GetEquipStatus().weaponNum == enInvalid) 
		{
			//装備がなければ描画しない
			m_equipWeapon[i].SetIsDraw(false);
		}
		//装備武器アイコンの枠の初期化
		texture = TextureResource().LoadTexture(L"Assets/sprite/Frame.png");
		m_equipFrame[i].Init(texture);
		m_equipFrame[i].SetSize({ 70.0f,70.0f });
		m_equipFrame[i].SetPosition(m_equipWeapon[i].GetPosition());
	}
	//装備リストを整理する
	EquipListReset();
	//ステータス表示を初期化
	SplayerStatus playerStatus = GetPlayer().GetStatus();
	CVector2 fontPos = { m_basePos.x + m_baseSize.x * m_width, m_basePos.y - 70.0f};
	wchar_t fontMoji[256];
	wchar_t fontNum[256];
	for (int j = 0; j < enFont_StatusNum; j++)
	{
		for (int i = 0; i < enStatus_Num; i++)
		{
			switch (i)
			{
			case enStatus_Hp:
				swprintf(fontMoji, L"最大HP : ");
				swprintf(fontNum, L"%d", playerStatus.MaxHealth);
				break;
			case enStatus_Attack:
				swprintf(fontMoji, L"攻撃力 : ");
				swprintf(fontNum, L"%d", playerStatus.Strength);
				break;
			case enStatus_Defense:
				swprintf(fontMoji, L"防御力 : ");
				swprintf(fontNum, L"%d", playerStatus.Defense);
				break;
			}
			m_statusFont[j][i].Init(fontMoji);
			m_statusFont[j][i].SetPosition({
				fontPos.x + 350.0f * j + 30.0f,
				fontPos.y - m_baseSize.y * i
			});
			CVector2 fontSize = { 0.7f, 0.7f };
			m_statusFont[j][i].SetSize(fontSize);

			m_statusFontNum[j][i].Init(fontNum);
			m_statusFontNum[j][i].SetPosition({
				fontPos.x + 350.0f * j + 160.0f,
				fontPos.y - m_baseSize.y * i
			});
			m_statusFontNum[j][i].SetSize(fontSize);
		}
	}
	//装備の名前を初期化
	m_equipName[enFont_CurrentStatus].Init(L"");
	m_equipName[enFont_CurrentStatus].SetSize({ 0.7f,0.7f });
	m_equipName[enFont_CurrentStatus].SetPosition({ 
		m_statusWindow[enFont_CurrentStatus].GetPosition().x - 100.0f,
		fontPos.y + m_baseSize.y - 30.0f
	});
	m_equipName[enFont_ChangeStatus].Init(L"");
	m_equipName[enFont_ChangeStatus].SetSize({ 0.7f,0.7f });
	m_equipName[enFont_ChangeStatus].SetPosition({
		m_statusWindow[enFont_ChangeStatus].GetPosition().x - 100.0f,
		fontPos.y + m_baseSize.y - 30.0f
	});

	m_equipSound[0].Init("Assets/sound/SystemSound/EquipOn.wav");
	m_equipSound[1].Init("Assets/sound/SystemSound/EquipOff.wav");
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

void CEquipInventory::PostAfterDraw()
{
	m_background.Draw();
	m_headline.Draw();
	m_inventoryWindow.Draw();
	for (int i = 0; i < CEquipList::m_equipLimit; i++)
	{
		m_frame[i].Draw();
	}
	std::list<std::unique_ptr<IInventoryEquip>>& equipList = GetEquipList().GetBody();
	for (auto& equip : equipList)
	{
		equip->Draw();
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
	m_buttonAMoji.Draw();
	m_buttonBMoji.Draw();
	m_buttonYMoji.Draw();
	for (int j = 0; j < enFont_StatusNum; j++)
	{
		for (int i = 0; i < enStatus_Num; i++)
		{
			m_statusFont[j][i].Draw();
			m_statusFontNum[j][i].Draw();
		}
		m_equipName[j].Draw();
	}
}

void CEquipInventory::EquipListReset()
{
	std::list<std::unique_ptr<IInventoryEquip>>& equipList = GetEquipList().GetBody();
	if (equipList.empty()) 
	{
		//装備が何もない
		return;
	}
	int idx = 0;
	for (auto& equip : equipList)
	{
		//座標を決める
		CVector2 position = m_basePos;
		position.x += m_baseSize.x * (idx % m_width);
		position.y -= m_baseSize.y * (idx / m_width);
		equip->GetSprite()->SetPosition(position);
		equip->GetSprite()->SetSize(m_baseSize);
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
	std::list<std::unique_ptr<IInventoryEquip>>& equipList = GetEquipList().GetBody();

	//装備の数を取得
	size_t equipNum = equipList.size();
	if (m_pointerNum >= equipNum || equipList.empty()) 
	{
		//選んだ場所の装備がリストの中にない又はリストが空になっている
		return;
	}
	//選んだ武器のアイコンを描画させる
	std::list<std::unique_ptr<IInventoryEquip>>::iterator it;
	it = equipList.begin();
	for (int i = 0; i < m_pointerNum; i++)
	{
		it++;
	}
	EnPlayerWeapon weaponNumber = (*it)->GetEquipStatus().weaponNum;
	m_equipWeapon[weaponNumber].SetIsDraw(true);
	//選んだ装備と現在の装備を交換する
	IInventoryEquip* weapon = GetPlayer().GetWeaponManager().GetEquipWeapon(weaponNumber);
	if (weapon->GetEquipStatus().weaponNum == enInvalid)
	{
		//何も装備していない
		GetPlayer().GetWeaponManager().SetEquipWeapon(std::move(*it), weaponNumber);
		equipList.erase(it);
	}
	else
	{
		//装備を交換する
		GetPlayer().GetWeaponManager().ChangeEquipWeapon(std::move(*it), weaponNumber);
		//空きができたのでリストから外す
		equipList.erase(it);
	}
	//装備リストを整理する
	EquipListReset();
	//装備時の音を鳴らす処理
	if (m_equipSound[0].IsPlay())
	{
		m_equipSound[0].Stop();
	}
	m_equipSound[0].Play(false, true);
}

void CEquipInventory::CalucStatus()
{
	std::list<std::unique_ptr<IInventoryEquip>>& equipList = GetEquipList().GetBody();

	//プレイヤーのステータスを取得
	SplayerStatus playerStatus = GetPlayer().GetStatus();
	//装備の数を取得
	size_t equipNum = equipList.size();
	SWeaponStatus equipStatus[enFont_StatusNum];
	if (m_pointerNum < equipNum) 
	{
		//所持している装備を選んでいる場合はその装備のステータスを取得
		std::list<std::unique_ptr<IInventoryEquip>>::iterator it;
		it = equipList.begin();
		for (int i = 0; i < m_pointerNum; i++)
		{
			it++;
		}
		equipStatus[enFont_ChangeStatus] = (*it)->GetEquipStatus();
		m_equipName[enFont_ChangeStatus].SetString((*it)->GetItemName());
	}
	else 
	{
		m_equipName[enFont_ChangeStatus].SetString(L"");
		m_equipName[enFont_CurrentStatus].SetString(L"");
	}

	if (equipStatus[enFont_ChangeStatus].weaponNum != EnPlayerWeapon::enInvalid)
	{
		//現在の装備のステータスを取得
		IInventoryEquip* equipWeapon = GetPlayer().GetWeaponManager().GetEquipWeapon(equipStatus[enFont_ChangeStatus].weaponNum);
		equipStatus[enFont_CurrentStatus] = equipWeapon->GetEquipStatus();
		m_equipName[enFont_CurrentStatus].SetString(equipWeapon->GetItemName());
	}

	//装備変更した場合のステータスを計算する
	wchar_t fontMoji[256];
	wchar_t fontNum[256];
	int status = 0;
	for (int j = 0; j < enFont_StatusNum; j++) 
	{
		for (int i = 0; i < enStatus_Num; i++)
		{
			switch (i)
			{
			case enStatus_Hp:
				status = playerStatus.MaxHealth;
				swprintf(fontMoji, L"最大HP : ");
				break;
			case enStatus_Attack:
				status = equipStatus[j].attack + playerStatus.Strength;
				swprintf(fontMoji, L"攻撃力 : ");
				break;
			case enStatus_Defense:
				status = equipStatus[j].diffence + playerStatus.Defense;
				swprintf(fontMoji, L"防御力 : ");
				break;
			}
			swprintf(fontNum, L"%d", status);
			//ステータスの文字と数値を設定
			m_statusFont[j][i].SetString(fontMoji);
			m_statusFontNum[j][i].SetString(fontNum);
		}
	}

	//ステータスが変化している場合はフォントの色を変える
	//高ければ赤色、低ければ青色
	for (int i = 0; i < enStatus_Num; i++)
	{
		CVector4 color = CVector4::Black;
		switch (i)
		{
		case enStatus_Attack:
			if (equipStatus[enFont_CurrentStatus].attack < equipStatus[enFont_ChangeStatus].attack)
			{
				color = CVector4::Blue;
			}
			else if (equipStatus[enFont_CurrentStatus].attack > equipStatus[enFont_ChangeStatus].attack)
			{
				color = CVector4::Red;
			}
			break;
		case enStatus_Defense:
			if (equipStatus[enFont_CurrentStatus].diffence < equipStatus[enFont_ChangeStatus].diffence)
			{
				color = CVector4::Blue;
			}
			else if (equipStatus[enFont_CurrentStatus].diffence > equipStatus[enFont_ChangeStatus].diffence)
			{
				color = CVector4::Red;
			}
			break;
		}
		m_statusFontNum[enFont_ChangeStatus][i].SetColor(color);
	}
}

void CEquipInventory::Erase()
{
	std::list<std::unique_ptr<IInventoryEquip>>& equipList = GetEquipList().GetBody();

	//装備の数を取得
	size_t equipNum = equipList.size();
	if (m_pointerNum >= equipNum || equipList.empty()) 
	{
		//選んだ場所の装備がリストの中にない又はリストが空になっている
		return;
	}
	//選んだ装備を捨てる
	std::list<std::unique_ptr<IInventoryEquip>>::iterator it;
	it = equipList.begin();
	for (int i = 0; i < m_pointerNum; i++)
	{
		it++;
	}
	equipList.erase(it);
	//装備リストを整理する
	EquipListReset();
	//装備を捨てるときの音を鳴らす処理
	if (m_equipSound[1].IsPlay())
	{
		m_equipSound[1].Stop();
	}
	m_equipSound[1].Play(false, true);
}
