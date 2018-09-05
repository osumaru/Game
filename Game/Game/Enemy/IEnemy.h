/*
*	敵のインターフェースクラス
*/

#pragma once

#include "../Enemy/EnemyState/EnemyStateMachine.h"

class IEnemy : public IGameObject
{
public:
	//コンストラクタ
	IEnemy();

	//デストラクタ
	virtual ~IEnemy();

	//初期化
	virtual void Init(CVector3 position) = 0;

	//更新
	virtual void Update() = 0;

	//描画
	virtual void Draw() = 0;

	//敵の座標を取得
	const CVector3& GetPosition()
	{
		return m_position;
	}

	//再生したいアニメーションの番号を設定
	void SetAnimNum(int animNum)
	{
		m_animNum = animNum;
	}

protected:
	CSkinModel				m_skinModel;			//スキンモデル
	CCharacterController	m_characterController;	//キャラクターコントローラー
	CAnimation				m_animation;			//アニメーション
	EnemyStateMachine		m_enemyStateMachine;	//ステートマシン
	CVector3				m_position;				//座標
	int						m_animNum = 0;			//再生するアニメーション番号
	int						m_animNumOld = 0;		//1つ前のアニメーション番号
};