#pragma once


class CPlayerState
{
public:
	enum EnPlayerState
	{
		enPlayerStand,			//待機アニメーション
		enPlayerWalk,			//歩行アニメーション
		enPlayerRun,			//走りアニメーション
		enPlayerRunJump,		//走りジャンプ
		enPlayerJump,			//ジャンプアニメーション
		enPlayerAttack,			//攻撃アニメーション
		enPlayerAttack2,		//連撃モーション
		enPlayerDamage,			//ダメージアニメーション
		enPlayerAvoidance,		//回避アニメーション
		enPlayerDied,			//死亡アニメーション
		enPlayerArrowAttack,	//弓のアニメーション
		enPlayerLongSwordAttack,//大剣の攻撃アニメーション
		enPlayerTwinSwordAttack,//二刀流の攻撃アニメーション
		enPlayerWireMove,	//ワイヤーアニメーション
		enPlayerNum,			//アニメーションの数
		enState_Invald,			//何もない
	};

	enum EnPlayerWepon
	{
		enSword,			//片手剣
		enLongSword,		//両手剣
		enArro,				//弓矢
		enTwinSword,		//二刀

	};
};