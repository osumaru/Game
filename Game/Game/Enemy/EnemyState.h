/*
*	エネミーの状態クラス
*/

#pragma once

class EnemyState {
public:
	enum EnState {
		enState_Idle,	//待機
		enState_Walk,	//歩き
		enState_Invald,	//何もない
	};
};