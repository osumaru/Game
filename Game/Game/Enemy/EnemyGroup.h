/*
*	エネミーのグループクラス
*/

#pragma once

#include "RespawnData.h"
#include "../Map/Map.h"
class IEnemy;


class CEnemyGroup : public IGameObject
{
public:
	//コンストラクタ
	CEnemyGroup() {}

	//デストラクタ
	virtual ~CEnemyGroup() {}

	//初期化
	//position		座標
	void Init(const CVector3& position)
	{
		m_position = position;
	}

	//更新
	void Update() override;

	//グループのリストに追加
	//enemy		エネミークラスのポインタ
	void Add(const SMapChipInfo& enemy);

	//座標を取得
	const CVector3& GetPosition() const
	{
		return m_position;
	}

	//エネミーが死んだときに呼ぶ関数
	void EnemyNumReduce()
	{
		m_groupNum--;
	}


	//グループ内のエネミー数を取得
	int GetGroupNum()
	{
		return m_groupNum;
	}

private:
	std::list<SMapChipInfo>		m_respawnDataList;	//初期座標のリスト(リスポーン時に使用する)
	CVector3					m_position;			//座標
	int							m_groupNum = 0;		//グループ内のエネミー数
	float						m_timer = 0.0f;		//タイマー
	const float					RESPAWN_TIME = 3.0f;//リスポーンする時間
};