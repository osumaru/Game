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
		enAnimation_Down,	//ダウン
		enAnimation_StandUp,//立ち上がる
		enAnimation_Death,	//死亡
		enAnimation_Num,	//状態の数
	};

	enum EnAnimationStateWarrok {
		enAnimationWarrok_Idle,		//待機
		enAnimationWarrok_Walk,		//歩き
		enAnimationWarrok_Chase,	//追従
		enAnimationWarrok_Attack,	//攻撃
		enAnimationWarrok_Damage,	//ダメージ
		enAnimationWarrok_Down,		//ダウン
		enAnimationWarrok_StandUp,	//立ち上がる
		enAnimationWarrok_Death,	//死亡
		enAnimationWarrok_throw,	//岩を投げる
		enAnimationWarrok_Num,		//状態の数
	};
};