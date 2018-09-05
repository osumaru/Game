/*
*	ゾンビクラス
*/

#pragma once

#include "Enemy/IEnemy.h"

class Zombie : public IEnemy
{
public:
	//コンストラクタ
	Zombie();

	//デストラクタ
	~Zombie();

	//初期化
	//position	座標
	void Init(CVector3 position);

	//更新
	void Update();

	//描画
	void Draw();

	//敵の座標を取得
	CVector3 GetPosition()
	{
		return m_position;
	}

private:
	CSkinModel				m_skinModel;			//スキンモデル
	CCharacterController	m_characterController;	//キャラクターコントローラー
	CAnimation				m_animation;			//アニメーション
	EnemyStateMachine		m_enemyStateMachine;	//ステートマシン
	CVector3				m_position;				//座標
};