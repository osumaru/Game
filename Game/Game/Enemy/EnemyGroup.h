/*
*	エネミーのグループクラス
*/

#pragma once

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
	void Init(CVector3 position)
	{
		m_position = position;
	}

	//更新
	void Update() override;

	//グループのリストに追加
	//enemy		エネミークラスのポインタ
	void Add(IEnemy* enemy)
	{
		m_enemyGroupList.push_back(enemy);
	}

	//座標を取得
	const CVector3& GetPosition()
	{
		return m_position;
	}

	//グループのリストを取得
	std::list<IEnemy*> GetGroupList()
	{
		return m_enemyGroupList;
	}

private:
	std::list<IEnemy*> m_enemyGroupList ;	//グループのリスト
	CVector3 m_position;					//座標
};