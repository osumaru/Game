/*
*	エネミーのグループクラス
*/

#pragma once

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
	void Add(IEnemy* enemy)
	{
		m_groupNum++;
		m_enemyGroupList.push_back({ enemy, m_groupNum });
	}

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
	std::list<SEnemyGroupData>	m_enemyGroupList ;	//グループのリスト
	CVector3					m_position;			//座標
	int							m_groupNum = 0;		//グループ内のエネミー数
};