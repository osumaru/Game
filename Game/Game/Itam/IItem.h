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
	virtual void Use() {};

	enum EnInventoryItemType {
		Recovery,	//回復
		Buff,		//バフ
		TypeNum,	//種類の数
		Invald		//何もない
	};

	//アイテムの種類を取得
	EnInventoryItemType GetItemType()
	{
		return m_itemType;
	}

	//アイテムが使用されたか
	bool GetIsUse()
	{
		return m_isUse;
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
	float					m_timer = 0.0f;				//タイマー
	bool					m_popEnd = false;			//ポップし終わったか
	bool					m_isUse = false;			//アイテムが使用されたか
};