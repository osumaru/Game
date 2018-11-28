/*
*	エネミーの状態クラス
*/

#pragma once

class CEnemyState {
public:
	enum EnState {
		enState_Idle,		//待機
		enState_Walk,		//歩き
		enState_Chase,		//追従
		enState_Attack,		//攻撃
		enState_AttackWait,	//攻撃後の待ち
		enState_Damage,		//ダメージ
		enState_Stan,		//スタン
		enState_Death,		//死亡
		enState_Num,		//状態の数
		enState_Invald,		//何もない
	};

	enum EnAnimationState {
		enAnimation_Idle,	//待機
		enAnimation_Walk,	//歩き
		enAnimation_Chase,	//追従
		enAnimation_Attack,	//攻撃
		enAnimation_Damage,	//ダメージ
		enAnimation_Death,	//死亡
		enAnimation_Num,	//状態の数
	};
};