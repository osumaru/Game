/*
*	エネミーのダメージクラス
*/

#pragma once

#include "IEnemyState.h"

class CDamageNumber;

class CEnemyDamage : public IEnemyState
{
public:
	//コンストラクタ
	//enemy		エネミーのインターフェースクラスのポインタ
	//esm		エネミーのステートマシンクラスのポインタ
	CEnemyDamage(IEnemy* enemy, CEnemyStateMachine* esm) :
		IEnemyState(enemy, esm)
	{
	}

	//デストラクタ
	~CEnemyDamage() {};

	//初期化
	void Init();

	//更新する前に一度だけ呼ばれる
	bool Start() override;

	//更新
	void Update() override;

	//ノックバック中かのフラグを取得
	bool IsNockBack() const
	{
		return m_isNockBack;
	}
private:
	CDamageNumber*	m_damageNumber = nullptr;	//ダメージ表示
	const float		m_knockBackSpeed = 5.0f;	//ノックバックスピード
	float			m_deceleration = 0.0f;		//減速力
	float			m_friction = 0.0f;			//摩擦力
	float			m_knockBackScale = 1.0f;	//ノックバックスピードの倍率
	bool			m_wasStanAttack = false;	//スタン攻撃を受けたか
	bool			m_isNockBack = false;		//ノックバック中かのフラグ
	CEffect			m_damageEffect;
};