#pragma once
class MapChip;
class IEnemy;
class Player;
class CEnemyGroup;
class INpcState;
//マップチップのタグ
enum EnMapChipTag
{
	enMapTagUntagged,		//タグなし
	enMapTagPlayer,			//プレイヤータグ
	enMapTagZombie,			//Zombieタグ
	enMapTagSamurai,		//Samuraiタグ
	enMapTagNinja,			//NInjaタグ
	enMapTagWarrok,			//Warrokタグ
	enMapTagMaw,			//Mawタグ
	enMapTagEnemyGroup,		//エネミーグループのタグ
	enMapTagMapChip,		//マップチップ
	enMapTagTerrain,		//地形用のタグ
	enMapTagShopNpc,		//店NPC用のタグ
	enMapTagBreakBrock,		//消せるオブジェクトのタグ
	enMapTagNum,			//タグの数
};

struct SMapChipInfo
{
	wchar_t*		m_modelName;	//モデル名
	CVector3		m_position;		//座標
	CQuaternion		m_rotation;		//回転
	EnMapChipTag	m_tag;			//タグ
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
	std::vector<CEnemyGroup*>	m_enemyGroupList;		//エネミーグループのベクター
	bool						m_collider = false;		//AABBを作成するかどうか
	std::list<INpcState*>		m_npcList;				//NPCのリスト
};
