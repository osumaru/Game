#pragma once

//�G�l�~�[�̎��
enum EnEnemyType
{
	enEnemy_Zombi,
	enEnemy_Samurai,
	enEnemy_Ninja,
	enEnemy_Warrok,
};

struct SRespawnData
{
	CVector3 initPosition;	//�������W
	EnEnemyType enemyType;	//�G�l�~�[�̎��
	int level;				//���x��
};
