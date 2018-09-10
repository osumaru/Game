/*
*	敵のインターフェースクラス
*/

#pragma once

#include "../Enemy/EnemyState/EnemyStateMachine.h"
#include "../UI/DamageNumber/DamageNumber.h"

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
	const CVector3& GetPosition() const
	{
		return m_position;
	}

	//再生したいアニメーションの番号を設定
	void SetAnimNum(int animNum)
	{
		m_animNum = animNum;
	}

	//アニメーションを再生
	void PlayAnimation(int animNum)
	{
		m_animation.Play(animNum);
	}

	//アニメーションを再生しているか
	bool IsPlayAnimation() const
	{
		return m_animation.IsPlay();
	}

	//エネミーのボーンのワールド行列を取得
	const CMatrix& GetBoneWorldMatrix(const wchar_t* boneName) const
	{
		return m_skinModel.FindBoneWorldMatrix(boneName);
	}

	//ステートマシンをゲームオブジェクトから解放
	void StateMachineRelease()
	{
		m_enemyStateMachine.Release();
	}

	//エネミーのダメージ計算
	void DamageCalculation()
	{
		m_damageNumber.DamageCalculation();
	}

	//ダメージ表示のリセット
	void DamageIndicateReset()
	{
		m_damageNumber.Reset();
	}

protected:
	CSkinModel				m_skinModel;			//スキンモデル
	CCharacterController	m_characterController;	//キャラクターコントローラー
	CAnimation				m_animation;			//アニメーション
	EnemyStateMachine		m_enemyStateMachine;	//ステートマシン
	CDamegeNumber			m_damageNumber;			//ダメージ数値
	CVector3				m_position;				//座標
	CQuaternion				m_rotation;				//回転
	int						m_animNum = 0;			//再生するアニメーション番号
	int						m_animNumOld = 0;		//1つ前のアニメーション番号
};