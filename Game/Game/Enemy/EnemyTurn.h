/*
*	エネミーの回転クラス
*/

#pragma once

class IEnemy;

class CEnemyTurn : public IGameObject
{
public:
	//コンストラクタ
	//enemy		エネミークラスのポインタ
	CEnemyTurn(IEnemy* enemy) :
		m_enemy(enemy)
	{
	}

	//更新
	void Update();

private:
	IEnemy* m_enemy;	//エネミー
};