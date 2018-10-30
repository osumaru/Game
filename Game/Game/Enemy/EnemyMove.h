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

	//移動しているか
	bool GetIsMove()
	{
		return m_isMove;
	}

	//移動速度を取得
	const CVector3& GetMoveSpeed() const
	{
		return m_characterController.GetMoveSpeed();
	}

	//移動速度を設定
	//moveSpeed		移動速度
	void SetMoveSpeed(const CVector3& moveSpeed)
	{
		m_characterController.SetMoveSpeed(moveSpeed);
	}

private:
	CCharacterController	m_characterController;			//キャラクターコントローラー
	IEnemy*					m_enemy = nullptr;				//エネミー
	CVector3				m_destination;					//移動先の座標
	int						m_interval = 0;
	bool					m_isMove = false;				//移動しているか
};