#include "stdafx.h"
#include "Menu.h"
#include "../../Player/Player.h"
#include "../../Map/Map.h"
#include "../../Scene/SceneManager.h"
#include "../../Enemy/IEnemy.h"
#include "../../Enemy/Maw.h"
#include "../../NPC/IShop.h"
#include "../../NPC/ShopManager.h"
#include "ItemInventory.h"
#include "EquipInventory.h"

CMenu::CMenu()
{
	SetIsActive(false);
}


CMenu::~CMenu()
{
}

void CMenu::BeforeDead()
{
	if (m_itemInventory!= nullptr)
	{
		Delete(m_itemInventory);
	}
	if (m_equipInventory != nullptr)
	{
		Delete(m_equipInventory);
	}
}

void CMenu::Init()
{
	m_menuSoundEffect.Init("Assets/sound/SystemSound/MenuOpen.wav", false);
	m_Texture = TextureResource().LoadTexture(L"Assets/sprite/MenuUI/Menu.png");
	m_menu.Init(m_Texture);
	m_menu.SetPosition({ -1.0f, -1.0f });
	m_menu.SetSize({ 1290.0f,720.0f });

	//�H�y���A�C�R��
	m_selectTexture = TextureResource().LoadTexture(L"Assets/sprite/MenuUI/Select.png");
	m_selectSprite.Init(m_selectTexture);
	m_selectPosition = SELECT_TEX_POS;
	m_selectSprite.SetPosition(m_selectPosition);
	m_selectSprite.SetSize(m_selectScale);
	wchar_t filePath[256];
	for (int i = 0; i < NUMBER_LINE; i++)
	{
		
		swprintf(filePath, L"0");
		m_numberFont[i].Init(filePath);
		m_numberFont[i].SetPosition(m_numberPos);
		if(i==4)
		{ 
			m_numberPos.y -= 45.0f;
		}
		m_numberPos.y -= 55.0f;
	}
	
	SetIsActive(true);
}


void CMenu::Update()
{
	if (&GetPlayer() == nullptr || GetPlayer().GetIsDied() || !GetPlayer().GetIsAction()) { return; }
	for (auto& shop : GetSceneManager().GetMap()->GetShop()->Getlist())
	{
		if (shop->GetShopState() != 0)
		{
			return;
		}
	}

	KeyInputMenu();
	switch (m_menuState)
	{
	case enMiniMap:			//�~�j�}�b�v�̊m�F
		
		break;

	case enItems:			//�C���x���g���̊m�F
		if (Pad().IsTriggerButton(enButtonA)) 
		{
			m_itemInventory = New<CItemInventory>(PRIORITY_UI);
			m_itemInventory->Init(this);
		}
		StatusConversion();
		break;

	case enWeapons:			//�����̊m�F
		if (Pad().IsTriggerButton(enButtonA))
		{
			m_equipInventory = New<CEquipInventory>(PRIORITY_UI);
			m_equipInventory->Init(this);
		}
		break;

	case enSaveGame:		//�f�[�^�̃Z�[�u
		
		break;

	case enExsitGame:		//�^�C�g����ʂɖ߂�
		
		break;
	case enNoneMenu:

		break;

	}

	
	
}

void CMenu::KeyInputMenu()
{
	//���j���[��ʂ��J���Ă鎞�����s������
	if (m_draw)
	{
		if (Pad().IsTriggerButton(enButtonDown) && m_selectPosition.y > UI_POSITION_Y_DOWN_LIMIT)
		{
			m_selectPosition.y -= UI_OFFSET_Y;
			m_selectSprite.SetPosition(m_selectPosition);
			m_stateNum++;
			m_menuState = (EnMenuState)m_stateNum;
		}

		else if (Pad().IsTriggerButton(enButtonUp) && m_selectPosition.y < UI_POSITION_Y_UP_LIMIT)
		{
			m_selectPosition.y += UI_OFFSET_Y;
			m_selectSprite.SetPosition(m_selectPosition);
			m_stateNum--;
			m_menuState = (EnMenuState)m_stateNum;
		}
	}

	//�Z���N�g�{�^���������ꂽ���̏���
	if (Pad().IsTriggerButton(enButtonSelect) || Pad().IsTriggerButton(enButtonB) && m_draw)
	{
		PlayerStatusInput();
		StatusMath();
		if (m_draw)
		{
			GetPlayer().SetIsAction(false);
			m_draw = false;
			m_menuState = enNoneMenu;
			m_stateNum = enNoneMenu;
			m_selectPosition = SELECT_TEX_POS;
			m_selectSprite.SetPosition(m_selectPosition);
			//������������
			if (m_menuSoundEffect.IsPlay())
			{
				m_menuSoundEffect.Stop();
			}
		}
		else
		{
			m_draw = true;
			m_menuState = enMiniMap;
			m_stateNum = enMiniMap;
			m_menuSoundEffect.Play(false,true);
			

		}
		std::list<IEnemy*> enemyList = GetSceneManager().GetMap()->GetEnemyList();
		
		//�G�̃A�N�e�B�u�ݒ�
		for (auto& enemy : enemyList)
		{
			enemy->SetIsActive(!m_draw);

		}
		for (auto& shop : GetSceneManager().GetMap()->GetShop()->Getlist())
		{
			shop->SetIsActive(!m_draw);
		}
		//�{�X�̓����̐ݒ�
		if (&GetMaw())
		{
			GetMaw().SetIsActive(!m_draw);
		}
		//�v���C���[�̓����̐ݒ�
		GetPlayer().SetIsActive(!m_draw);

	}

	if (Pad().IsTriggerButton(enButtonSelect))
	{
		//�v���C���[�̃X�e�[�^�X���i�[
		PlayerStatusInput();
		//�\�����鐔�l���v�Z���鏈��
		StatusMath();
	}

	
}

void CMenu::PlayerStatusInput()
{
	m_PlayerStatus[0] = GetPlayer().GetStatus().Health;
	m_PlayerStatus[1] = GetPlayer().GetStatus().Level;
	m_PlayerStatus[2] = GetPlayer().GetStatus().Strength;
	m_PlayerStatus[3] = GetPlayer().GetStatus().Defense;
	m_PlayerStatus[4] = GetPlayer().GetStatus().ExperiencePoint;
	m_PlayerStatus[5] = GetPlayer().GetStatus().NextExp;
	m_PlayerStatus[6] = GetPlayer().GetStatus().Gold;

}

void CMenu::StatusConversion()
{
	if (!GetPlayer().GetIsStatusConversion()) { return; }
	PlayerStatusInput();
	StatusMath();
	GetPlayer().SetIsStatusConversion(false);
}


//���j���[��ʂɕ\�������v���C���[�̃X�e�[�^�X�̐��l�����߂鏈��
void CMenu::StatusMath()
{


	for (int i = 0; i < NUMBER_LINE; i++)
	{
			wchar_t filePath[256];
			int Box = m_PlayerStatus[i];
			swprintf(filePath, L"%d", Box);
			m_numberFont[i].SetString(filePath);
	}


}

//���j���[��ʂ̕`�揈��
void CMenu::PostAfterDraw()
{
	if (GetPlayer().GetIsDied()) { return; }
	if (m_draw)
	{
		m_menu.Draw();
		m_selectSprite.Draw();
		for (auto& fonts : m_numberFont)
		{
			fonts.Draw();
		}
	}
}