#pragma once

//プレイヤーアニメーションの列挙型
enum EnPlayerAnimation
{
	enPlayerAnimationStand,			//待機アニメーション
	enPlayerAnimationWalk,			//歩行アニメーション
	enPlayerAnimationRun,			//走りアニメーション
	enPlayerAnimationRunJump,		//走りジャンプ
	enPlayerAnimationJump,			//ジャンプアニメーション
	enPlayerAnimationAttack,		//攻撃アニメーション
	enPlayerAnimationAttack2,		//連撃アニメーション
	enPlayerAnimationAttack3,		//連撃アニメーション
	enPlayerAnimationAttackCombine,		//連撃アニメーション
	enPlayerAnimationDamage,		//ダメージアニメーション
	enPlayerAnimationAvoidance,		//回避アニメーション
	enPlayerAnimationAvoidanceCombine,	//回避の後の合成用ポーズのアニメーション
	enPlayerAnimationDete,			//死亡アニメーション
	enPlayerAnimationWireMove,		//ワイヤー移動アニメーション
	enPlayerAnimationArrowAttack,	//弓のアニメーション
	enPlayerAnimationArrowShoot,	//弓を放つアニメーション
	enPlayerAnimationLongSwordAttack,//大剣の攻撃アニメーション
	enPlayerAnimationTwinSwordAttack,//二刀流の攻撃アニメーション
	enPlayerAnimationLanding,//着地アニメーション
	enPlayerAnimationNum			//アニメーションの数
};


class CPlayerState
{
public:
	//ステートマシンの列挙型
	enum EnPlayerState
	{
		enPlayerStateStand,				//待機ステート
		enPlayerStateWalk,				//歩行ステート
		enPlayerStateRun,				//走りステート
		enPlayerStateRunJump,			//走りジャンプ
		enPlayerStateJump,				//ジャンプステート
		enPlayerStateAttack,			//攻撃ステート
		enPlayerStateDamage,			//ダメージステート
		enPlayerStateStun,				//スタンステート
		enPlayerStateAvoidance,			//回避ステート
		enPlayerStateDied,				//死亡ステート
		enPlayerStateWireMove,			//ワイヤーステート
		enPlayerStateArrowAttack,		//弓のステート
		enPlayerStateArrowShoot,		//弓を放つステート
		enPlayerStateLongSwordAttack,	//大剣の攻撃ステート
		enPlayerStateTwinSwordAttack,	//二刀流の攻撃ステート
	};
};