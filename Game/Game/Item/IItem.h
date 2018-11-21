/*
*	アイテムクラスのインターフェース
*/

#pragma once

class IItem : public IGameObject
{
public:
	//コンストラクタ
	IItem();

	//デストラクタ
	virtual ~IItem();

	//更新する前に一度だけ呼ばれる
	virtual bool Start() { return true; }

	//更新
	virtual void Update() = 0;

	//描画
	virtual void Draw() {};

	//アイテムを使う
	virtual bool Use() { return false; }

	//ランダム地点にポップさせる
	//distance	ランダム地点までの距離
	//upSpeed	ポップさせる上方向の速度
	virtual void RamdomPop(float distance, float upSpeed);

	//アイテムを拾うことができるか
	//isPopEnd	ポップし終わっているか
	//length	アイテムを拾える距離
	virtual bool PickUp(bool isPopEnd, float length);

	//属性
	enum EnInventoryItemType {
		Recovery,	//回復
		Buff,		//バフ
		Equip,		//装備
		TypeNum,	//種類の数
		Invald		//何もない
	};
	//プレイヤーの何に影響を与えるのか
	enum EnIemEffectPlayerStatus
	{
		Strength,		//攻撃力
		Defense,		//守備力
		Health,			//体力
		None,			//効果なし
	};
	//装備の情報アイテムの場合はNoWeapon
	enum EnWeaponType
	{
		enSword,			//片手剣
		enLongSword,		//両手剣
		enArrow,			//弓矢
		enTwinSword,		//二刀
		enNoWeapon,			//武器ではない
	};

	struct SItemStatus
	{
		wchar_t					ItemName[40];			//アイテムの名前
		int						ItemID = 0;				//商品の番号
		int						Itemprice = 0;			//アイテムの値段
		int						ItemEffect = 0;			//効果値
		EnIemEffectPlayerStatus	ItemEffectPlayerStatus = EnIemEffectPlayerStatus::None;
		EnInventoryItemType		ItemType = Invald;		//そのアイテムが回復系なのか装備するものなのかを判別する
		EnWeaponType			WeaponType = enNoWeapon;
	};

	//アイテムの種類を取得
	EnInventoryItemType GetItemType()
	{
		return m_itemType;
	}

protected:
	EnInventoryItemType		m_itemType = Invald;		//インベントリのアイテムの種類
	CSkinModel				m_skinModel;				//スキンモデル
	CVector3				m_position;					//座標
	CQuaternion				m_rotation;					//回転
	CCharacterController	m_characterController;		//キャラクターコントローラー
	CVector3				m_popPosition;				//アイテムがポップする座標
	CVector3				m_moveSpeed;				//移動速度
	const float				m_speed = 4.0f;				//速度
	const float				m_deadTime = 30.0f;			//アイテムが消滅するまでの時間
	float					m_timer = 0.0f;				//タイマー
};