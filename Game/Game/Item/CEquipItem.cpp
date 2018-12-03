#include "stdafx.h"
#include "CEquipItem.h"


CEquipItem::CEquipItem()
{
}


CEquipItem::~CEquipItem()
{
}


//後でデータから読み込ます
bool CEquipItem::Start()
{
	//片手剣の初期化
	{
		swprintf(ItemStatus[0].ItemName, L"ヒノキの剣");
		swprintf(ItemStatus[0].ItemText, L"ヒノ木で作られた木剣。\n子供たちが好んで使っている。");
		ItemStatus[0].Itemprice = 10;
		ItemStatus[0].ItemEffect = 5;
		ItemStatus[0].ItemQuality = EnItemQuality::enNormal;
		swprintf(ItemStatus[1].ItemName, L"銅の剣 ");
		swprintf(ItemStatus[1].ItemText, L"銅で作られた剣。\n護身用として好んで\n使っている。");
		ItemStatus[1].Itemprice = 50;
		ItemStatus[1].ItemEffect = 10;
		ItemStatus[1].ItemQuality = EnItemQuality::enNormal;
		swprintf(ItemStatus[2].ItemName, L"鉄の剣 ");
		swprintf(ItemStatus[2].ItemText, L"鉄で作られた剣。\n兵士や傭兵、冒険者が\n愛用している。");
		ItemStatus[2].Itemprice = 100;
		ItemStatus[2].ItemEffect = 75;
		ItemStatus[2].ItemQuality = EnItemQuality::enNormal;
		swprintf(ItemStatus[3].ItemName, L"鋼の剣 ");
		swprintf(ItemStatus[3].ItemText, L"鋼で作られた剣。\n騎士や兵隊長など上位職の者\nが愛用している。");
		ItemStatus[3].Itemprice = 250;
		ItemStatus[3].ItemEffect = 40;
		ItemStatus[3].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[4].ItemName, L"魔法の剣");
		swprintf(ItemStatus[4].ItemText, L"魔力が込められた剣。\n一部の上流階級のみが\n所持している。");
		ItemStatus[4].Itemprice = 1500;
		ItemStatus[4].ItemEffect = 250;
		ItemStatus[4].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[5].ItemName, L"ロングソード ");
		swprintf(ItemStatus[5].ItemText, L"通常の片手剣より長い剣。\n馬上で敵を討つために\n作られた。");
		ItemStatus[5].Itemprice = 550;
		ItemStatus[5].ItemEffect = 110;
		ItemStatus[5].ItemQuality = EnItemQuality::enRare;
		ItemStatus[5].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[6].ItemName, L"バイキングソード");
		swprintf(ItemStatus[6].ItemText, L"ある民族が使用していた剣。\n民族の中でも上流階級の者が\n愛用していた武器。");
		ItemStatus[6].Itemprice = 740;
		ItemStatus[6].ItemEffect = 130;
		ItemStatus[6].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[7].ItemName, L"古びた剣");
		swprintf(ItemStatus[7].ItemText, L"さび付いた剣。\nかなりの年月が経っており\n武器としてはほとんど意味をなさない。");
		ItemStatus[7].Itemprice = 1000;
		ItemStatus[7].ItemEffect = 5;
		ItemStatus[7].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[8].ItemName, L"ショートソード");
		swprintf(ItemStatus[8].ItemText, L"一般的な片手剣。\n主に歩兵が愛用している。");
		ItemStatus[8].Itemprice = 120;
		ItemStatus[8].ItemEffect = 30;
		ItemStatus[8].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[9].ItemName, L"英雄の剣");
		swprintf(ItemStatus[9].ItemText, L"国の英雄のみに贈られる剣。\n一振りで敵を屠ることのできる\n強力な力を秘めている。");
		ItemStatus[9].Itemprice = 9999;
		ItemStatus[9].ItemEffect = 999;
		ItemStatus[9].ItemQuality = EnItemQuality::enLegend;

		for (int num = 0;num < 10 /*MAX_ITEM_NUMBER*/;num++)
		{
			ItemStatus[num].ItemID = num + 1;
			ItemStatus[num].WeaponType = EnPlayerWeapon::enWeaponSword;
			ItemStatus[num].ItemEffectPlayerStatus = EnIemEffectPlayerStatus::Strength;
			ItemStatus[num].ItemType = EnInventoryItemType::Equip;
			//ノーマルアイテムのIDの入ったリスト作成
			if (ItemStatus[num].ItemQuality == EnItemQuality::enNormal)
			{
				m_normalEquipItemList.push_back(ItemStatus[num].ItemID);
			}
			//レアアイテムのIDの入ったリスト作成
			else if (ItemStatus[num].ItemQuality == EnItemQuality::enRare)
			{
				m_rareEquipItemList.push_back(ItemStatus[num].ItemID);
			}
			else
			{

			}
			m_equipItemStatusList.push_back(ItemStatus[num]);
		
		}
	}

	//両手の初期化
	{
		swprintf(ItemStatus[10].ItemName, L"グレートソード");
		ItemStatus[10].Itemprice = 800;
		ItemStatus[10].ItemEffect = 70;
		ItemStatus[10].ItemQuality = EnItemQuality::enNormal;
		swprintf(ItemStatus[11].ItemName, L"バスターソード");
		ItemStatus[11].Itemprice = 1200;
		ItemStatus[11].ItemEffect = 150;
		ItemStatus[11].ItemQuality = EnItemQuality::enNormal;
		swprintf(ItemStatus[12].ItemName, L"クレイモア");
		ItemStatus[12].Itemprice = 860;
		ItemStatus[12].ItemEffect = 120;
		ItemStatus[12].ItemQuality = EnItemQuality::enNormal;
		swprintf(ItemStatus[13].ItemName, L"ツヴァイハンダー");
		ItemStatus[13].Itemprice = 650;
		ItemStatus[13].ItemEffect = 100;
		ItemStatus[13].ItemQuality = EnItemQuality::enNormal;
		swprintf(ItemStatus[14].ItemName, L"騎士の大剣");
		ItemStatus[14].Itemprice = 700;
		ItemStatus[14].ItemEffect = 130;
		ItemStatus[14].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[15].ItemName, L"炎の大剣");
		ItemStatus[15].Itemprice = 3500;
		ItemStatus[15].ItemEffect = 450;
		ItemStatus[15].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[16].ItemName, L"氷の大剣");
		ItemStatus[16].Itemprice = 3500;
		ItemStatus[16].ItemEffect = 450;
		ItemStatus[16].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[17].ItemName, L"雷の大剣");
		ItemStatus[17].Itemprice = 3500;
		ItemStatus[17].ItemEffect = 450;
		ItemStatus[17].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[18].ItemName, L"丸太");
		ItemStatus[18].Itemprice = 10;
		ItemStatus[18].ItemEffect = 20;
		ItemStatus[18].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[19].ItemName, L"英雄の大剣");
		ItemStatus[19].Itemprice = 9999;
		ItemStatus[19].ItemEffect = 999;
		ItemStatus[19].ItemQuality = EnItemQuality::enLegend;
		for (int num = 10;num < 20 /*MAX_ITEM_NUMBER*/;num++)
		{
			ItemStatus[num].ItemID = num + 1;
			ItemStatus[num].WeaponType = EnPlayerWeapon::enWeaponLongSword;
			ItemStatus[num].ItemEffectPlayerStatus = EnIemEffectPlayerStatus::Strength;
			ItemStatus[num].ItemType = EnInventoryItemType::Equip;
			//ノーマルアイテムのIDの入ったリスト作成
			if (ItemStatus[num].ItemQuality == EnItemQuality::enNormal)
			{
				m_normalEquipItemList.push_back(ItemStatus[num].ItemID);
			}
			//レアアイテムのIDの入ったリスト作成
			else if (ItemStatus[num].ItemQuality == EnItemQuality::enRare)
			{
				m_rareEquipItemList.push_back(ItemStatus[num].ItemID);
			}
			else
			{

			}
			m_equipItemStatusList.push_back(ItemStatus[num]);
		}
	}

	return true;
}

void CEquipItem::Update()
{

}
