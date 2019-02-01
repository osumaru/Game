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
		swprintf(ItemStatus[0].ItemText,L"ヒノキで作られた木剣\n子供たちが好んで使っている");
		ItemStatus[0].Itemprice = 10;
		ItemStatus[0].ItemEffect = 10;
		ItemStatus[0].ItemQuality = EnItemQuality::enNormal;
		swprintf(ItemStatus[1].ItemName, L"銅の剣");
		swprintf(ItemStatus[1].ItemText, L"銅で作られた剣\n護身用として使っている");
		ItemStatus[1].Itemprice = 100;
		ItemStatus[1].ItemEffect = 20;
		ItemStatus[1].ItemQuality = EnItemQuality::enNormal;
		swprintf(ItemStatus[2].ItemName, L"鉄の剣");
		swprintf(ItemStatus[2].ItemText, L"鉄で作られた剣\n兵士が愛用してる");
		ItemStatus[2].Itemprice = 250;
		ItemStatus[2].ItemEffect = 25;
		ItemStatus[2].ItemQuality = EnItemQuality::enNormal;
		swprintf(ItemStatus[3].ItemName, L"鋼の剣");
		swprintf(ItemStatus[3].ItemText, L"鋼で作られた剣\n騎士が愛用している");
		ItemStatus[3].Itemprice = 460;
		ItemStatus[3].ItemEffect = 45;
		ItemStatus[3].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[4].ItemName, L"魔法の剣");
		swprintf(ItemStatus[4].ItemText, L"魔力が込められた剣\n上流階級のみが所持している");
		ItemStatus[4].Itemprice = 3000;
		ItemStatus[4].ItemEffect = 70;
		ItemStatus[4].ItemQuality = EnItemQuality::enLegend;
		swprintf(ItemStatus[5].ItemName, L"ロングソード");
		swprintf(ItemStatus[5].ItemText, L"通常の片手剣より長い剣\n馬上で敵を討つために\n作られた");
		ItemStatus[5].Itemprice = 1200;
		ItemStatus[5].ItemEffect = 55;
		ItemStatus[5].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[6].ItemName, L"バイキングソード");
		swprintf(ItemStatus[6].ItemText, L"ある民族が使用していた剣");
		ItemStatus[6].Itemprice = 1500;
		ItemStatus[6].ItemEffect = 58;
		ItemStatus[6].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[7].ItemName, L"古びた剣");
		swprintf(ItemStatus[7].ItemText, L"さび付いた剣\nかなりの年月が経っており\n武器としては意味をなさない");
		ItemStatus[7].Itemprice = 1000;
		ItemStatus[7].ItemEffect = 5;
		ItemStatus[7].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[8].ItemName, L"ショートソード");
		swprintf(ItemStatus[8].ItemText, L"一般的な片手剣\n歩兵が愛用している");
		ItemStatus[8].Itemprice = 200;
		ItemStatus[8].ItemEffect = 22;
		ItemStatus[8].ItemQuality = EnItemQuality::enNormal;
		swprintf(ItemStatus[9].ItemName, L"英雄の剣");
		swprintf(ItemStatus[9].ItemText, L"国の英雄のみに贈られる剣\n一振りで敵を屠る強力な\n力を秘めている");
		ItemStatus[9].Itemprice = 99999;
		ItemStatus[9].ItemEffect = 120;
		ItemStatus[9].ItemQuality = EnItemQuality::enSpecial;

		for (int num = 0;num < 10;num++)
		{
			//ID割り振り
			ItemStatus[num].ItemID = num + 1;
			//武器の種類の設定
			ItemStatus[num].WeaponType = EnPlayerWeapon::enWeaponSword;
			//インベントリに表示するスプライトの情報
			swprintf(ItemStatus[num].ItemSprite, L"Assets/sprite/sword.png");
			//影響を及ぼすステータス
			ItemStatus[num].ItemEffectPlayerStatus = EnIemEffectPlayerStatus::Strength;
			//装備のタイプの設定
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
			else if (ItemStatus[num].ItemQuality == EnItemQuality::enLegend)
			{
				m_legendEquipItemList.push_back(ItemStatus[num].ItemID);
			}
			m_equipItemStatusList.push_back(ItemStatus[num]);
		
		}
	}

	//両手の初期化
	{
		swprintf(ItemStatus[10].ItemName, L"グレートソード");
		swprintf(ItemStatus[10].ItemText, L"巨大な大剣\n力に任せ周囲の物を粉砕する\n恐ろしい力を秘めている。");
		ItemStatus[10].Itemprice = 100;
		ItemStatus[10].ItemEffect = 25;
		ItemStatus[10].ItemQuality = EnItemQuality::enNormal;
		swprintf(ItemStatus[11].ItemName, L"バスターソード");
		swprintf(ItemStatus[11].ItemText, L"バスターソード。グレー\nトソードと同じく、敵を\n粉砕するために作\nられた強力な大剣。");
		ItemStatus[11].Itemprice = 380;
		ItemStatus[11].ItemEffect = 30;
		ItemStatus[11].ItemQuality = EnItemQuality::enNormal;
		swprintf(ItemStatus[12].ItemName, L"クレイモア");
		swprintf(ItemStatus[12].ItemText, L"クレイモア。重たい一撃\n手歩兵を粉砕する大剣。");
		ItemStatus[12].Itemprice = 2600;
		ItemStatus[12].ItemEffect = 60;
		ItemStatus[12].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[13].ItemName, L"ツヴァイハンダー");
		swprintf(ItemStatus[13].ItemText, L"ツヴァイハンダー。振り\n回すことにより、より強\n力な一撃を放つ。");
		ItemStatus[13].Itemprice = 2700;
		ItemStatus[13].ItemEffect = 63;
		ItemStatus[13].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[14].ItemName, L"騎士の大剣");
		swprintf(ItemStatus[14].ItemText, L"騎士の大剣。兵隊長や王\nの側近の兵が身に着けて\nいる。");
		ItemStatus[14].Itemprice = 4000;
		ItemStatus[14].ItemEffect = 80;
		ItemStatus[14].ItemQuality = EnItemQuality::enLegend;
		swprintf(ItemStatus[15].ItemName, L"炎の大剣");
		swprintf(ItemStatus[15].ItemText, L"炎の大剣。炎の魔力が込\nめられた大剣。");
		ItemStatus[15].Itemprice = 7000;
		ItemStatus[15].ItemEffect = 100;
		ItemStatus[15].ItemQuality = EnItemQuality::enLegend;
		swprintf(ItemStatus[16].ItemName, L"氷の大剣");
		swprintf(ItemStatus[16].ItemText, L"氷の大剣。氷の魔力が込\nめられた大剣。");
		ItemStatus[16].Itemprice = 7000;
		ItemStatus[16].ItemEffect = 100;
		ItemStatus[16].ItemQuality = EnItemQuality::enLegend;
		swprintf(ItemStatus[17].ItemName, L"雷の大剣");
		swprintf(ItemStatus[17].ItemText, L"雷の大剣。雷の魔力が込\nめられた大剣。");
		ItemStatus[17].Itemprice = 7000;
		ItemStatus[17].ItemEffect = 100;
		ItemStatus[17].ItemQuality = EnItemQuality::enLegend;
		swprintf(ItemStatus[18].ItemName, L"丸太");
		swprintf(ItemStatus[18].ItemText, L"丸太。武器のとしての実\n用性はないが、これを振\nり回す筋力は計り知れない。");
		ItemStatus[18].Itemprice = 10;
		ItemStatus[18].ItemEffect = 10;
		ItemStatus[18].ItemQuality = EnItemQuality::enNormal;
		swprintf(ItemStatus[19].ItemName, L"英雄の大剣");
		swprintf(ItemStatus[19].ItemText, L"国の英雄のみに贈られる\n大剣。一振りで周囲の敵\nを粉砕する強力な力を秘めている。");
		ItemStatus[19].Itemprice = 99999;
		ItemStatus[19].ItemEffect = 150;
		ItemStatus[19].ItemQuality = EnItemQuality::enSpecial;
		for (int num = 10;num < 20;num++)
		{
			ItemStatus[num].ItemID = num + 1;
			ItemStatus[num].WeaponType = EnPlayerWeapon::enWeaponLongSword;
			//インベントリに表示するスプライトの情報
			swprintf(ItemStatus[num].ItemSprite, L"Assets/sprite/largeSword.png");
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
			else if (ItemStatus[num].ItemQuality == EnItemQuality::enLegend)
			{
				m_legendEquipItemList.push_back(ItemStatus[num].ItemID);
			}
			m_equipItemStatusList.push_back(ItemStatus[num]);
		}
	}

	//弓の初期化
	{
		swprintf(ItemStatus[20].ItemName, L"木の弓");
		swprintf(ItemStatus[20].ItemText, L"木でできた弓。駆け出しの\n冒険者が使用することが\n多い。");
		ItemStatus[20].Itemprice = 10;
		ItemStatus[20].ItemEffect = 5;
		ItemStatus[20].ItemQuality = EnItemQuality::enNormal;
		swprintf(ItemStatus[21].ItemName, L"旅人の弓");
		swprintf(ItemStatus[21].ItemText, L"旅人の弓。主に旅をする者た\nちが食料を確保するため\nに使用している。");
		ItemStatus[21].Itemprice = 50;
		ItemStatus[21].ItemEffect = 7;
		ItemStatus[21].ItemQuality = EnItemQuality::enNormal;
		swprintf(ItemStatus[22].ItemName, L"兵士の弓");
		swprintf(ItemStatus[22].ItemText, L"兵士の弓。主に兵士が戦争時に\n敵を屠るために使われて\nいる。");
		ItemStatus[22].Itemprice = 240;
		ItemStatus[22].ItemEffect = 15;
		ItemStatus[22].ItemQuality = EnItemQuality::enNormal;
		swprintf(ItemStatus[23].ItemName, L"森人の弓");
		swprintf(ItemStatus[23].ItemText, L"森人の弓。森人が狩りに使う弓。\n特殊な力が込められてい\nる。");
		ItemStatus[23].Itemprice = 600;
		ItemStatus[23].ItemEffect = 25;
		ItemStatus[23].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[24].ItemName, L"ボロイ弓");
		swprintf(ItemStatus[24].ItemText, L"ボロイ弓。弓を飛ばすことができる\nが、さほど威力はない。");
		ItemStatus[24].Itemprice = 0;
		ItemStatus[24].ItemEffect = 1;
		ItemStatus[24].ItemQuality = EnItemQuality::enNormal;
		swprintf(ItemStatus[25].ItemName, L"ロングボウ");
		swprintf(ItemStatus[25].ItemText, L"ロングボウ。通常の弓より大きく、そ\nの弓から放たれる一撃\nを重たい。");
		ItemStatus[25].Itemprice = 1200;
		ItemStatus[25].ItemEffect = 40;
		ItemStatus[25].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[26].ItemName, L"巨人の弓");
		swprintf(ItemStatus[26].ItemText, L"巨人の弓。古の時代にいた巨人族が使用\nしていた弓。");
		ItemStatus[26].Itemprice = 2500;
		ItemStatus[26].ItemEffect = 50;
		ItemStatus[26].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[27].ItemName, L"古代の弓");
		swprintf(ItemStatus[27].ItemText, L"古代の弓。古の時代の技術によって作られ\nた強力な弓。");
		ItemStatus[27].Itemprice = 4500;
		ItemStatus[27].ItemEffect = 65;
		ItemStatus[27].ItemQuality = EnItemQuality::enLegend;
		swprintf(ItemStatus[28].ItemName, L"賢者の弓");
		swprintf(ItemStatus[28].ItemText, L"賢者の弓。ある、賢者が使用していた弓。強\n力な魔力が込めら\nれている。。");
		ItemStatus[28].Itemprice = 8000;
		ItemStatus[28].ItemEffect = 76;
		ItemStatus[28].ItemQuality = EnItemQuality::enLegend;
		swprintf(ItemStatus[29].ItemName, L"英雄の弓");
		swprintf(ItemStatus[29].ItemText, L"国の英雄のみに贈られる弓。敵を一撃で屠る強\n力な矢を放つ。");
		ItemStatus[29].Itemprice = 99999;
		ItemStatus[29].ItemEffect = 90;
		ItemStatus[29].ItemQuality = EnItemQuality::enSpecial;
		for (int num = 20;num < 30;num++)
		{
			ItemStatus[num].ItemID = num + 1;
			ItemStatus[num].WeaponType = EnPlayerWeapon::enWeaponArrow;
			//インベントリに表示するスプライトの情報
			swprintf(ItemStatus[num].ItemSprite, L"Assets/sprite/bow.png");
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
			else if (ItemStatus[num].ItemQuality == EnItemQuality::enLegend)
			{
				m_legendEquipItemList.push_back(ItemStatus[num].ItemID);
			}
			m_equipItemStatusList.push_back(ItemStatus[num]);
		}
	}
	//弓の初期化
	{
		swprintf(ItemStatus[30].ItemName, L"木の双剣");
		swprintf(ItemStatus[30].ItemText, L"木でできた双剣。\n駆け出しの冒険者が使用している。");
		ItemStatus[30].Itemprice = 10;
		ItemStatus[30].ItemEffect = 4;
		ItemStatus[30].ItemQuality = EnItemQuality::enNormal;

		swprintf(ItemStatus[31].ItemName, L"バタフライソード");
		swprintf(ItemStatus[31].ItemText, L"旅人の弓。主に旅をする者た\nちが食料を確保するため\nに使用している。");
		ItemStatus[31].Itemprice = 120;
		ItemStatus[31].ItemEffect = 10;
		ItemStatus[31].ItemQuality = EnItemQuality::enNormal;

		swprintf(ItemStatus[32].ItemName, L"兵士の双刀");
		swprintf(ItemStatus[32].ItemText, L"兵士の弓。主に兵士が戦争時に\n敵を屠るために使われて\nいる。");
		ItemStatus[32].Itemprice = 340;
		ItemStatus[32].ItemEffect = 14;
		ItemStatus[32].ItemQuality = EnItemQuality::enNormal;

		swprintf(ItemStatus[33].ItemName, L"グラディウス");
		swprintf(ItemStatus[33].ItemText, L"森人の弓。森人が狩りに使う弓。\n特殊な力が込められてい\nる。");
		ItemStatus[33].Itemprice = 3500;
		ItemStatus[33].ItemEffect = 40;
		ItemStatus[33].ItemQuality = EnItemQuality::enRare;

		swprintf(ItemStatus[34].ItemName, L"盗賊のダガー");
		swprintf(ItemStatus[34].ItemText, L"ボロイ弓。弓を飛ばすことができる\nが、さほど威力はない。");
		ItemStatus[34].Itemprice = 500;
		ItemStatus[34].ItemEffect = 20;
		ItemStatus[34].ItemQuality = EnItemQuality::enNormal;

		swprintf(ItemStatus[35].ItemName, L"ファルシオン");
		swprintf(ItemStatus[35].ItemText, L"ロングボウ。通常の弓より大きく、そ\nの弓から放たれる一撃\nを重たい。");
		ItemStatus[35].Itemprice = 2400;
		ItemStatus[35].ItemEffect = 30;
		ItemStatus[35].ItemQuality = EnItemQuality::enLegend;

		swprintf(ItemStatus[36].ItemName, L"ショーテル");
		swprintf(ItemStatus[36].ItemText, L"巨人の弓。古の時代にいた巨人族が使用\nしていた弓。");
		ItemStatus[36].Itemprice = 1500;
		ItemStatus[36].ItemEffect = 25;
		ItemStatus[36].ItemQuality = EnItemQuality::enRare;

		swprintf(ItemStatus[37].ItemName, L"ツインソード");
		swprintf(ItemStatus[37].ItemText, L"古代の弓。古の時代の技術によって作られ\nた強力な弓。");
		ItemStatus[37].Itemprice = 1200;
		ItemStatus[37].ItemEffect = 23;
		ItemStatus[37].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[38].ItemName, L"メフィストフェレス");
		swprintf(ItemStatus[38].ItemText, L"賢者の弓。ある、賢者が使用していた弓。強\n力な魔力が込めら\nれている。。");
		ItemStatus[38].Itemprice = 4500;
		ItemStatus[38].ItemEffect = 46;
		ItemStatus[38].ItemQuality = EnItemQuality::enLegend;

		swprintf(ItemStatus[39].ItemName, L"英雄の双剣");
		swprintf(ItemStatus[39].ItemText, L"国の英雄のみに贈られる双剣。\n。");
		ItemStatus[39].Itemprice = 99999;
		ItemStatus[39].ItemEffect = 60;
		ItemStatus[39].ItemQuality = EnItemQuality::enSpecial;

		for (int num = 30;num < 40;num++)
		{
			ItemStatus[num].ItemID = num + 1;
			ItemStatus[num].WeaponType = EnPlayerWeapon::enWeaponTwinSword;
			//インベントリに表示するスプライトの情報
			swprintf(ItemStatus[num].ItemSprite, L"Assets/sprite/twinSword.png");
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
			else if (ItemStatus[num].ItemQuality == EnItemQuality::enLegend)
			{
				m_legendEquipItemList.push_back(ItemStatus[num].ItemID);
			}
			m_equipItemStatusList.push_back(ItemStatus[num]);
		}
	}
	//データの取得処理
	/*std::fstream file;
	file.open("Assets/ItemList/Equip.dta", std::ios::binary | std::ios::out | std::ios::trunc);
	file.write((char*)ItemStatus, sizeof(ItemStatus));
	file.close();
	file.open("Assets/ItemList/Equip.dta", std::ios::binary | std::ios::in);
	for (auto& list : ItemStatus)
	{
		file.read((char*)&list, sizeof(SItemStatus));
	}
	file.close();*/
	return true;
}

void CEquipItem::Update()
{

}
