/*
*	エネミーの移動クラス
*/

#pragma once

class IEnemy;

class CEnemyMove : public IGameObject
{
public:
	//コンストラクタ
	//enemy		エネミーのインターフェースクラスのポインタ
	CEnemyMove(IEnemy* enemy) :
		m_enemy(enemy)
	{
	}

	//更新が呼ばれる前に一度だけ呼ばれる
	bool Start();

	//更新
	void Update();

private:
	CCharacterController	m_characterController;			//キャラクターコントローラー
	IEnemy*					m_enemy = nullptr;				//エネミー
	CVector3				m_moveSpeed = CVector3::Zero;	//移動速度
};