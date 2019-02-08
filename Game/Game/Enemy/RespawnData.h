#pragma once

//エネミーの種類
enum EnEnemyType
{
	enEnemy_Zombi,
	enEnemy_Samurai,
	enEnemy_Ninja,
	enEnemy_Warrok,
};

struct SRespawnData
{
	CVector3 initPosition;	//初期座標
	EnEnemyType enemyType;	//エネミーの種類
	int level;				//レベル
};
