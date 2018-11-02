#include "stdafx.h"
#include "Menu.h"
#include "../../Player/Player.h"
#include "../../Map/Map.h"
#include "../../Scene/SceneManager.h"
#include "../../Enemy/IEnemy.h"
#include "ItemInventory.h"

CMenu::CMenu()
{
}


CMenu::~CMenu()
{
}


void CMenu::Init()
{
	m_Texture.Load(L"Assets/sprite/MenuUI/Menu.png");
	m_menu.Init(&m_Texture);
	m_menu.SetPosition({ -1.0f, -1.0f });
	m_menu.SetSize({ 1290.0f,720.0f });

	//�H�y���A�C�R��
	m_menuUITexture.Load(L"Assets/sprite/MenuUI/Select.png");
	m_menuUI.Init(&m_menuUITexture);
	m_menuUI.SetPosition(m_menuUIPosition);
	m_menuUI.SetSize(m_menuUIScale);

	for (int i = 0; i < NUMBER_LINE; i++)
	{
		for (int j = 0; j < NUMBER_COLUMN; j++)
		{
			m_numberTexture[i][j] = new CTexture;
			m_number[i][j] = new CSprite;
			m_numberTexture[i][j] = TextureResource().LoadTexture(L"Assets/sprite/number/number0.png");
			m_number[i][j]->Init(m_numberTexture[i][j]);
			m_number[i][j]->SetPosition({ m_numberPos});
			m_number[i][j]->SetSize({ 65.0f,65.0f });
			m_numberPos.x += 30.0;
		}
		if(i==4)
		{ 
			m_numberPos.y -= 43.0f;
		}
		m_numberPos.x = 500.0f;
		m_numberPos.y -= 57.0f;
	}
}


void CMenu::Update()
{
	if (GetPlayer().GetIsDied()) { return; }

	KeyInputMenu();
	switch (m_MenuState)
	{
	case enMiniMap:			//�~�j�}�b�v�̊m�F
		
		break;

	case enItems:			//�C���x���g���̊m�F
		if (Pad().IsTriggerButton(enButtonA)) 
		{
			m_itemInventory = New<CItemInventory>(0);
			m_itemInventory->Init(this);
		}
		break;

	case enWeapons:			//�����̊m�F
		
		break;

	case enSaveGame:		//�f�[�^�̃Z�[�u
		
		break;

	case enExsitGame:		//�^�C�g����ʂɖ߂�
		
		break;

	}

	
	
}

void CMenu::KeyInputMenu()
{
	//���j���[��ʂ��J���Ă鎞�����s������
	if (m_Draw)
	{
		if (Pad().IsTriggerButton(enButtonDown) && m_menuUIPosition.y > UI_POSITION_Y_DOWN_LIMIT)
		{
			m_menuUIPosition.y -= UI_OFFSET_Y;
			m_menuUI.SetPosition(m_menuUIPosition);
			m_StateNum++;
			m_MenuState = (EnMenuState)m_StateNum;
		}

		else if (Pad().IsTriggerButton(enButtonUp) && m_menuUIPosition.y < UI_POSITION_Y_UP_LIMIT)
		{
			m_menuUIPosition.y += UI_OFFSET_Y;
			m_menuUI.SetPosition(m_menuUIPosition);
			m_StateNum--;
			m_MenuState = (EnMenuState)m_StateNum;
		}
	}

	//�Z���N�g�{�^���������ꂽ���̏���
	if (Pad().IsTriggerButton(enButtonSelect))
	{
		StatusMath();
		if (m_Draw)
		{

			m_Draw = false;
		}
		else
		{
			m_Draw = true;

		}
		std::list<IEnemy*> enemyList = GetSceneManager().GetGameScene().GetMap()->GetEnemyList();
		//�G�̃A�N�e�B�u�ݒ�
		for (auto& enemy : enemyList)
		{
			enemy->SetIsActive(!m_Draw);

		}
		//�v���C���[�̓����̐ݒ�
		GetPlayer().SetIsActive(!m_Draw);
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


//���j���[��ʂɕ\�������v���C���[�̃X�e�[�^�X�̐��l�����߂鏈��
void CMenu::StatusMath()
{


	for (int i = 0; i < NUMBER_LINE; i++)
	{
		
			
			wchar_t filePath[256];
			//1000�̈�
			int Box = m_PlayerStatus[i] / 1000;
			swprintf(filePath, L"Assets/sprite/number/number%d.png", Box);
			{
				if (Box == 0)
				{
					m_number[i][0]->SetIsDraw(false);
				}
				else
				{

					m_numberTexture[i][0] = m_numberTexture[i][0] = TextureResource().LoadTexture(filePath);
					m_number[i][0]->SetTexture(m_numberTexture[i][0]);
					m_PlayerStatus[i] %= 1000;
					m_number[i][0]->SetIsDraw(true);
				}

			}

			//100�̈�
			Box = m_PlayerStatus[i] / 100;
			swprintf(filePath, L"Assets/sprite/number/number%d.png",Box );
			{
				if (Box == 0 && !m_number[i][0]->IsDraw())
				{
					m_number[i][1]->SetIsDraw(false);
				}
				else
				{

					m_numberTexture[i][1] = m_numberTexture[i][1] = TextureResource().LoadTexture(filePath);
					m_number[i][1]->SetTexture(m_numberTexture[i][1]);
					m_PlayerStatus[i] %= 100;
					m_number[i][1]->SetIsDraw(true);
				}
			}

			//10�̈�
			Box = m_PlayerStatus[i] / 10;
			swprintf(filePath, L"Assets/sprite/number/number%d.png", Box);
			{
				if (Box == 0 && !m_number[i][1]->IsDraw())
				{
					m_number[i][2]->SetIsDraw(false);
				}
				else
				{

					m_numberTexture[i][2] = m_numberTexture[i][2] = TextureResource().LoadTexture(filePath);
					m_number[i][2]->SetTexture(m_numberTexture[i][2]);
					m_PlayerStatus[i] %= 10;
					m_number[i][2]->SetIsDraw(true);
				}

			}

			//1�̈�
			swprintf(filePath, L"Assets/sprite/number/number%d.png", m_PlayerStatus[i]);
			m_numberTexture[i][3] = m_numberTexture[i][3] = TextureResource().LoadTexture(filePath);
			m_numberTexture[i][3]->Load(filePath);
			m_number[i][3]->SetTexture(m_numberTexture[i][3]);

	
	}


}

//���j���[��ʂ̕`�揈��
void CMenu::AfterDraw()
{
	if (GetPlayer().GetIsDied()) { return; }
	if (m_Draw)
	{
		m_menu.Draw();
		m_menuUI.Draw();
		for (int i = 0; i < NUMBER_LINE; i++)
		{
			for (int j = 0; j < NUMBER_COLUMN; j++)
			{

				m_number[i][j]->Draw();
			}
		}

	}


}