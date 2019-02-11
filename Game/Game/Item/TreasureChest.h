/*
*	装備アイテムクラス
*/

#pragma once

#include "IItem.h"
#include "InventoryItem/IInventoryEquip.h"

class CTreasureChest : public IItem
{
public:
	enum EnDropType
	{
		enRandom,			//決められたドロップ率からランダムに取り出す。
		enNormal,			//レア度1の入ったリストからアイテムを取り出す
		enRare,				//レア度2の入ったリストからアイテムを取り出す
		enLegend,			//レア度3の入ったリストからアイテムを取り出す
		enSpecial,			//レア度4の入ったリストからアイテムを取り出す
	};
	//初期化
	//position		座標
	//isMapItem		マップに配置するか
	void Init(CVector3 position, CQuaternion rotation = {0.00f, 0.00f, 0.00f, 1.00f}, bool isMapItem = false, EnDropType dropType = enRandom);

	//更新する前に一度だけ呼ばれる
	bool Start() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//武器のステータスを決める
	void DesideWeaponStatus();

private:
	std::unique_ptr<IInventoryEquip> m_inventoryEquip;	//インベントリに入れる装備
	EnDropType	m_dropType = EnDropType::enRandom;
	CLight	m_light;				//ライト
	bool m_itemDrawCount = false;	//アイテムを拾うUIを出すカウントをすでにしているか
	bool m_isMapItem = false;		//マップに配置するか
	std::unique_ptr<CRigidBody>			m_rigidBody;		//剛体
	std::unique_ptr<CMeshCollider>		m_meshCollider;		//コライダー
	std::unique_ptr<CBoxCollider>		m_boxCollider;		//コライダー
	bool								m_isItemeName = false;
	bool								m_isDrawItemName = false;
	float								m_drawTime = 0.0f;
};