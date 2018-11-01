#pragma once
class MapChip;
class IEnemy;
class Player;
class INpcState;

//マップチップのタグ
enum EnMapChipTag
{
	enMapTagUntagged,
	enMapTagPlayer,
	enMapTagZombie,
	enMapTagSamurai,
	enMapTagNinja,
	enMapTagWarrok,
	enMapTagEnemyGroup,
	enMapTagMapChip,
	enMapTagTerrain,		//地形用のタグ
	enMapTagShopNpc,			//店NPC用のタグ
	enMapTagNum,
};

struct SMapChipInfo
{
	wchar_t*			m_modelName;
	CVector3		m_position;
	CQuaternion	m_rotation;
	EnMapChipTag	m_tag;
};

//マップのオブジェクトを配置するクラス

class Map : public IGameObject
{
public:
	//コンストラクタ
	Map();

	//デストラクタ
	~Map();

	//初期化
	void Init(int stageNum);


	//更新関数
	void Update()override;

	//死ぬ前に一度だけ呼ばれる
	void BeforeDead()override;

	
	/*
	マップチップをデリート
	iterator	デリートするマップチップのイテレーター
	*/
	void MapChipErase(std::list<MapChip*>::iterator iterator);

	//エネミーのリストを取得
	std::list<IEnemy*> GetEnemyList()
	{
		return m_enemyList;
	}

private:
	std::list<MapChip*>			m_mapChip;				//マップチップ
	std::list<IEnemy*>			m_enemyList;			//エネミーリスト
	std::list<INpcState*>		m_npcList;				//NPCのリスト
	bool						m_collider = false;
};
