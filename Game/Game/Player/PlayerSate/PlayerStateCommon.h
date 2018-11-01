#pragma once

enum EnPlayerAnimation
{
	enPlayerAnimationStand,			//待機アニメーション
	enPlayerAnimationWalk,			//歩行アニメーション
	enPlayerAnimationRun,			//走りアニメーション
	enPlayerAnimationRunJump,		//走りジャンプ
	enPlayerAnimationJump,			//ジャンプアニメーション
	enPlayerAnimationAttack,		//攻撃アニメーション
	enPlayerAnimationAttack2,		//連撃アニメーション
	enPlayerAnimationDamage,		//ダメージアニメーション
	enPlayerAnimationAvoidance,		//回避アニメーション
	enPlayerAnimationDete,			//死亡アニメーション
	enPlayerAnimationWireMove,		//ワイヤー移動アニメーション
	enPlayerAnimationArrowAttack,	//弓のアニメーション
	enPlayerAnimationArrowShoot,	//弓を放つアニメーション
	enPlayerAnimationLongSwordAttack,//大剣の攻撃アニメーション
	enPlayerAnimationTwinSwordAttack,//二刀流の攻撃アニメーション
	enPlayerAnimationNum				//アニメーションの数
};

class CPlayerState
{
public:
	enum EnPlayerState
	{
		enPlayerStateStand,				//待機アニメーション
		enPlayerStateWalk,				//歩行アニメーション
		enPlayerStateRun,				//走りアニメーション
		enPlayerStateRunJump,			//走りジャンプ
		enPlayerStateJump,				//ジャンプアニメーション
		enPlayerStateAttack,			//攻撃アニメーション
		enPlayerStateDamage,			//ダメージアニメーション
		enPlayerStateAvoidance,			//回避アニメーション
		enPlayerStateDied,				//死亡アニメーション
		enPlayerStateWireMove,			//ワイヤーアニメーション
		enPlayerStateArrowAttack,		//弓のアニメーション
		enPlayerStateArrowShoot,		//弓を放つアニメーション
		enPlayerStateLongSwordAttack,	//大剣の攻撃アニメーション
		enPlayerStateTwinSwordAttack,	//二刀流の攻撃アニメーション
		enPlayerStateNum,				//アニメーションの数
	};

	enum EnPlayerWepon
	{
		enSword,			//片手剣
		enLongSword,		//両手剣
		enArro,				//弓矢
		enTwinSword,		//二刀

	};
};