/*
*	アイテムクラスのインターフェース
*/

#pragma once
#include "../Player/Weapon/WeaponCommon.h"
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

	//ランダム地点にポップさせる
	//distance	ランダム地点までの距離
	//upSpeed	ポップさせる上方向の速度
	virtual void RamdomPop(float distance, float upSpeed);

	//アイテムを拾うことができるか
	//isPopEnd	ポップし終わっているか
	//length	アイテムを拾える距離
	virtual bool PickUp(bool isPopEnd, float length);

	//移動
	virtual CVector3 Move();

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
	//アイテムのクオリティー
	enum EnItemQuality
	{
		enNormal,
		enRare,
		enLegend,
	};

	struct SItemStatus
	{
		wchar_t					ItemName[40];							//アイテムの名前
		wchar_t					ItemText[100];							//武器の説明
		int						ItemID = 0;								//商品の番号
		int						Itemprice = 0;							//アイテムの値段
		int						ItemEffect = 0;							//効果値
		EnItemQuality			ItemQuality = EnItemQuality::enNormal;	//アイテムのクオリティー
		EnIemEffectPlayerStatus	ItemEffectPlayerStatus = EnIemEffectPlayerStatus::None;
		EnInventoryItemType		ItemType = Invald;						//そのアイテムが回復系なのか装備するものなのかを判別する
		EnPlayerWeapon			WeaponType = EnPlayerWeapon::enInvalid;	//装備の種類
	};


protected:
	CSkinModel				m_skinModel;				//スキンモデル
	CVector3				m_position;					//座標
	CQuaternion				m_rotation;					//回転
	CCharacterController	m_characterController;		//キャラクターコントローラー
	const float				m_deadTime = 30.0f;			//アイテムが消滅するまでの時間
	float					m_timer = 0.0f;				//タイマー
	float					m_accele = 0.0f;
	bool					m_isPopEnd = false;			//ポップし終わったか
	bool					m_isMove = false;
};