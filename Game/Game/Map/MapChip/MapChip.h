#pragma once
//マップで配置するオブジェクトの基底クラス
class Player;
#include "../Map.h"

class MapChip : public IGameObject
{
public:

	//コンストラクタ
	MapChip();

	//デストラクタ
	virtual ~MapChip();

	/*
	初期化する関数
	position	座標
	rotation	回転
	modelName	読み込むモデルの名前
	anim		アニメーション付きのモデルの場合アニメーションを入れる入れ物
	*/
	virtual void Init(const CVector3& position, const CQuaternion& rotation, const wchar_t* modelName, const bool collider, CAnimation* anim = nullptr);

	//初期化関数
	virtual bool Start()override;

	//更新関数
	virtual void Update()override;

	//描画関数
	virtual void Draw()override;

	/*
	イテレーターをセット
	map			自身をデリートするためのインスタンス
	iterator	自身のイテレーター
	*/
	void SetIterator(Map* map, std::list<MapChip*>::iterator iterator);

	//アクティブかのフラグを設定する
	/*void SetIsActive(bool isActive)
	{
		m_isActive = isActive;
	}*/

protected:
	//デリートする関数
	void MapChipDelete();

protected:
	CSkinModel		m_skinModel;				//スキンモデル
	CVector3		m_position;					//座標
	CQuaternion		m_rotation;					//回転
	CVector3		m_scale;					//拡大
	Map*			m_pMap;						//デリートする時のためのポインタ
	std::list<MapChip*>::iterator m_iterator;	//自身のイテレーター
	bool			m_isActive;					//アクティブか？
	CMatrix			m_worldMatrix;
};