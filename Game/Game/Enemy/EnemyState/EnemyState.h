/*
*	エネミーの状態クラス
*/

#pragma once

class CEnemyState {
public:
	enum EnState {
		enState_Idle,	//待機
		enState_Walk,	//歩き
		enState_Chase,	//追従
		enState_Attack,	//攻撃
		enState_Damage,	//ダメージ
		enState_Death,	//死亡
		enState_Num,	//状態の数
		/////////////
		enState_Stan,	//スタン
		/////////////
		enState_Invald,	//何もない
	};
};