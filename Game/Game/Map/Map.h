#pragma once
class CTreasureChest;
class CSea;
class MapChip;
class BreakMapObject;
class IEnemy;
class Player;
class CEnemyGroup;
class CShopManager;
//マップチップのタグ
enum EnMapChipTag
{
	enMapTagUntagged,
	enMapTagPlayer,
	enMapTagMaw,
	enMapTagZombie,
	enMapTagSamurai,
	enMapTagNinja,
	enMapTagWarrok,
	enMapTagEnemyGroup,
	enMapTagMapChip,
	enMapTagBreakBrock,
	enMapTagTerrain,		//地形用のタグ
	enMapTagMesh,			//剛体をメッシュにするためのタグ
	enMapTagItemShop,		//アイテムショップ用のタグ
	enMapTagWeaponShop,		//武器屋用のタグ
	enMapTagSoundPoint,		//BGM用のタグ
	enMapTagTree,			//木のモデルに着けるタグ
	enMapTagTreasureBox,	//宝箱用のタグ
	enMapTagSea,			//水面
	enMapTagObstacle,
	enMapTagBossObj,
	enMapTagTitleEnemy,
	enMapTagNum,
};

struct SMapChipInfo
{
	wchar_t*		m_modelName;
	CVector3		m_position;
	CQuaternion		m_rotation;
	EnMapChipTag	m_tag;
	int				m_level = 0;
	int				m_dropType = 0;
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
	std::list<IEnemy*>& GetEnemyList()
	{
		return m_enemyList;
	}

	//エネミーグループのリストを取得
	std::list<CEnemyGroup*>& GetEnemyGroupList()
	{
		return m_enemyGroupList;
	}

	CShopManager* GetShop()
	{
		return m_shopManager;
	}

private:
	std::list<MapChip*>			m_mapChip;				//マップチップ
	std::list<IEnemy*>			m_enemyList;			//エネミーリスト
	std::list<CEnemyGroup*>		m_enemyGroupList;		//エネミーグループのリスト
	std::list<CTreasureChest*>	m_treasureList;			//宝箱リスト`
	bool						m_collider = false;		//AABBを作成するかどうか
	bool						m_isTree = false;	//木用のコライダーの設定をするためのフラグ		
	CShopManager*				m_shopManager;
};