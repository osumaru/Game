#pragma once

//プレイヤーアニメーションの列挙型
enum EnPlayerAnimation
{
	enPlayerAnimationStand,			//待機アニメーション
	enPlayerAnimationWalk,			//歩行アニメーション
	enPlayerAnimationRun,			//走りアニメーション
	enPlayerAnimationDash,			//ダッシュアニメーション
	enPlayerAnimationRunJump,		//走りジャンプ
	enPlayerAnimationJump,			//ジャンプアニメーション
	enPlayerAnimationAttack1,		//攻撃アニメーション
	enPlayerAnimationAttack2,		//連撃アニメーション
	enPlayerAnimationAttack3,		//連撃アニメーション
	enPlayerAnimationAttackCombine1,		//連撃の後の合成用アニメーション
	enPlayerAnimationAttackCombine2,		//連撃の後の合成用アニメーション
	enPlayerAnimationAttackCombine3,		//連撃の後の合成用アニメーション
	enPlayerAnimationLeageAttack1,		//攻撃アニメーション
	enPlayerAnimationLeageAttack2,		//連撃アニメーション
	enPlayerAnimationLeageAttack3,		//連撃アニメーション
	enPlayerAnimationLeageAttackCombine1,		//連撃の後の合成用アニメーション
	enPlayerAnimationLeageAttackCombine2,		//連撃の後の合成用アニメーション
	enPlayerAnimationLeageAttackCombine3,		//連撃の後の合成用アニメーション
	enPlayerAnimationTwinAttack1,		//攻撃アニメーション
	enPlayerAnimationTwinAttack2,		//連撃アニメーション
	enPlayerAnimationTwinAttack3,		//連撃アニメーション
	enPlayerAnimationTwinAttackCombine1,		//連撃の後の合成用アニメーション
	enPlayerAnimationTwinAttackCombine2,		//連撃の後の合成用アニメーション
	enPlayerAnimationTwinAttackCombine3,		//連撃の後の合成用アニメーション
	enPlayerAnimationAttackAir,		//攻撃(空中)アニメーション
	enPlayerAnimationRunSword,		//納刀前の剣を持ってる状態のアニメーション
	enPlayerAnimationRunTwinSword,		//納刀前の双剣を持ってる状態のアニメーション
	enPlayerAnimationRunLeageSword,	//納刀前の大剣を持ってる状態のアニメーション
	enPlayerAnimationStun,			//スタン用のアニメーション
	enPlayerAnimationDamage,		//ダメージアニメーション
	enPlayerAnimationDamageAir,		//ダメージ(空中)アニメーション
	enPlayerAnimationAvoidance,		//回避アニメーション
	enPlayerAnimationAvoidanceCombine,	//回避の後の合成用ポーズのアニメーション
	enPlayerAnimationDete,			//死亡アニメーション
	enPlayerAnimationWireThrow,		//ワイヤーを投げるアニメーション
	enPlayerAnimationWireMove,		//ワイヤー移動アニメーション
	enPlayerAnimationWireAttack,	//ワイヤー攻撃アニメーション
	enPlayerAnimationArrowAttack,	//弓のアニメーション
	enPlayerAnimationArrowShoot,	//弓を放つアニメーション
	enPlayerAnimationLongSwordAttack,//大剣の攻撃アニメーション
	enPlayerAnimationTwinSwordAttack,//二刀流の攻撃アニメーション
	enPlayerAnimationLanding,		//着地アニメーション
	enPlayerAnimationDown,			//空中から落ちるアニメーション
	enPlayerAnimationUp,			//起き上がりアニメーション
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
		enPlayerStateJump,				//ジャンプステート
		enPlayerStateAttack,			//攻撃ステート
		enPlayerStateDamage,			//ダメージステート
		enPlayerStateStun,				//スタンステート
		enPlayerStateAvoidance,			//回避ステート
		enPlayerStateDied,				//死亡ステート
		enPlayerStateWireMove,			//ワイヤーステート
		enPlayerStateWireAttack,		//ワイヤー攻撃ステート
		enPlayerStateArrowAttack,		//弓のステート
		enPlayerStateArrowShoot,		//弓を放つステート
		enPlayerStateSky,				//空中にいるステート
		enPlayerStateDown,				//ダウンステート
		enPlayerStateNum,				//ステートの数
	};
};