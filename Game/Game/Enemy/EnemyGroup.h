/*
*	エネミーのグループクラス
*/

#pragma once

#include "RespawnData.h"

class IEnemy;

struct SEnemyGroupData
{
	IEnemy* enemy;
	int groupNumber;
};

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
	void Add(IEnemy* enemy);

	//座標を取得
	const CVector3& GetPosition() const
	{
		return m_position;
	}

	//グループのリストを取得
	std::list<SEnemyGroupData> GetGroupList()
	{
		return m_enemyGroupList;
	}

	//グループ内のエネミー数を取得
	int GetGroupNum()
	{
		return m_groupNum;
	}

private:

	struct SRespawnData
	{
		CVector3 initPosition;	//初期座標
		EnEnemyType enemyType;	//エネミーの種類
		int level;
	};

	std::list<SEnemyGroupData>	m_enemyGroupList ;	//グループのリスト
	std::list<SRespawnData>		m_respawnDataList;	//初期座標のリスト(リスポーン時に使用する)
	CVector3					m_position;			//座標
	int							m_groupNum = 0;		//グループ内のエネミー数
	float						m_timer = 0.0f;
	const float					RESPAWN_TIME = 3.0f;
};