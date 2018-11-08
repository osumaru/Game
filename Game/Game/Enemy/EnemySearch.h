/*
*	エネミー探索クラス
*/

#pragma once

class IEnemy;

class CEnemySearch : public IGameObject
{
public:
	//コンストラクタ
	//enemy		エネミーのインターフェースクラスのポインタ
	CEnemySearch(IEnemy* enemy) :
		m_enemy(enemy)
	{
	}

	//更新
	void Update() override;

private:
	IEnemy* m_enemy = nullptr;	//エネミー
};