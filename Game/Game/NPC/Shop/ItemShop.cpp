#include "stdafx.h"
#include "ItemShop.h"
#include "../../Player/Player.h"
#include "../../Camera/GameCamera.h"


CItemShop::CItemShop()
{
}


CItemShop::~CItemShop()
{
}

void CItemShop::Init(const CVector3 position, const CQuaternion rotation)
{
	m_position = position;
	m_rotation = rotation;
	m_skinModel.Load(L"Assets/modelData/U2.cmo", NULL);
	m_backTexture.Load(L"Assets/sprite/Back_Texture.png");
	m_backSprite.Init(&m_backTexture);
	m_backSprite.SetPosition({10.0f,95.0f});
	m_backSprite.SetSize({ 625.0f,325.0f });

	m_shopLineuoTexture.Load(L"Assets/sprite/ShopUI/Potion/BluePotion.png");
	m_shopSelectTexture[0].Load(L"Assets/sprite/ShopUI/Buy.png");
	m_shopSelect[0].Init(&m_shopSelectTexture[0]);
	m_shopSelectTexture[1].Load(L"Assets/sprite/ShopUI/Execute.png");
	m_shopSelect[1].Init(&m_shopSelectTexture[1]);

	m_shopSelectPenTexture.Load(L"Assets/sprite/MenuUI/Select2.png");
	m_shopSelectPen.Init(&m_shopSelectPenTexture);
	m_shopSelectPen.SetPosition(m_shopSelectPenPosition);
	m_shopSelectPen.SetSize(m_shopSelectPenSize);

	m_selectItemTexture.Load(L"Assets/sprite/ShopUI/SelectItem.png");
	m_selectItemSprite.Init(&m_selectItemTexture);
	m_selectItemSprite.SetPosition(m_slectItemTexPos);
	m_selectItemSprite.SetSize(m_selectItemTexSize);


	for (int num = 0;num < SELECT_TEX_ELEMENT;num++)
	{
		m_shopSelect[num].SetPosition(m_shopSelectPosition);
		m_shopSelect[num].SetSize(m_shopSelectSize);
		m_shopSelectPosition.y -= 100.0f;
	}

	for (int y_num = 0; y_num < Y_ELEMENT;y_num++)
	{
		for (int x_num = 0; x_num < X_ELEMENT;x_num++)
		{
			m_shopLineup[y_num][x_num].Init(&m_shopLineuoTexture);
			m_shopLineup[y_num][x_num].SetSize(m_shopLineupTexSize);
			m_shopLineup[y_num][x_num].SetPosition(m_shopLineupPosition);
			m_shopLineupPosition.x += SHOPLINEUP_POSITION_OFFSET.x;
			m_price[y_num][x_num] = Random().GetRandInt() % 300 + 100;
		}
		m_shopLineupPosition.x -= SHOPLINEUP_POSITION_OFFSET.x * X_ELEMENT;
		m_shopLineupPosition.y -= SHOPLINEUP_POSITION_OFFSET.y;
	}
}

void CItemShop::Update()
{
	ShopUpdate();
	
}

void CItemShop::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
	
}
void CItemShop::AfterDraw()
{
	if(!m_isSelectDraw && !m_isShoplineupDraw) { return; }

	for (int num = 0;num < SELECT_TEX_ELEMENT;num++)
	{
		m_shopSelect[num].Draw();

	}
	m_shopSelectPen.Draw();

	if (!m_isShoplineupDraw) { return; }
	m_backSprite.Draw();
	m_selectItemSprite.Draw();
	for (int y_num = 0; y_num < Y_ELEMENT;y_num++)
	{
		for (int x_num = 0; x_num < X_ELEMENT;x_num++)
		{
			m_shopLineup[y_num][x_num].Draw();;
			
		}
		
	}
}