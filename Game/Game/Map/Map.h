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
	enMapTagNormalShop,		//取引しない店のモデルのためのタグ
	enMapTagSoundPoint,		//BGM用のタグ
	enMapTagTree,			//木のモデルに着けるタグ
	enMapTagTreasureBox,	//宝箱用のタグ
	enMapTagSea,			//水面
	enMapTagCastle,			//Castle系のモデルのタグ(Zアップでナビゲーションメッシュからパスを取り除く為ののモデル
	enMapTagObstacle,
	enMapTagBossObj,
	enMapTagTitleEnemy,
	enMapTagDirectionalLight,
	enMapTagNum,
};

struct SMapChipInfo
{
	wchar_t*		m_modelName;
	CVector3		m_position;
	CQuaternion		m_rotation;
	EnMapChipTag	m_tag;
	bool			m_isShadowCaster;
	bool			m_isShadowReceiver;
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
	void MapChipErase(std::list<MapChip*>::iterator iterator, int areaPosX, int areaPosY);



	//エネミーグループのリストを取得
	std::list<CEnemyGroup*>& GetEnemyGroupList()
	{
		return m_enemyGroupList;
	}

	CShopManager* GetShop()
	{
		return m_shopManager;
	}

	//マップのオブジェクトにアクティブフラグを設定
	//void SetIsMapChipActive(bool isActive);

	//マップのオブジェクトのアップデートのアクティブフラグを設定
	void SetIsMapChipActiveUpdate(bool isActive);

	//空間分割の一辺あたりの分割数
	static const int AREA_PARTITION_NUM = 10;

	//分割したエリアの範囲
	float GetPartitionRange() const
	{
		return m_partitionRange;
	}
	
	//X軸のエリア位置を求める
	int GetAreaPosX(const CVector3& position)
	{
		int areaPosX = position.x;
		areaPosX += m_partitionRange * AREA_PARTITION_NUM * 0.5f;
		areaPosX /= m_partitionRange;
		return areaPosX;
	}

	//Y軸のエリア位置を求める
	int GetAreaPosY(const CVector3& position)
	{
		int areaPosY = position.z;
		areaPosY += m_partitionRange * AREA_PARTITION_NUM * 0.5f;
		areaPosY /= m_partitionRange;
		return areaPosY;
	}

	//指定したエリア内にあるマップチップを取得
	std::list<MapChip*>& GetMapChips(int areaPosX, int areaPosY)
	{
		return m_mapChips[areaPosX][areaPosY];
	}


	//マップチップを制作
	void CreateMapChip(const SMapChipInfo& info);


private:
	//プレイヤーの周りの空間のみアクティブにする
	//void PlayerAroundAreaActive();
private:
	int						m_playerAreaPosX = 0;
	int						m_playerAreaPosY = 0;
	std::list<MapChip*>		m_mapChips[AREA_PARTITION_NUM][AREA_PARTITION_NUM];
	MapChip*				m_ground = nullptr;
	std::list<CEnemyGroup*>		m_enemyGroupList;		//エネミーグループのリスト
	//std::list<CTreasureChest*>	m_treasureList;			//宝箱リスト`
	CShopManager*				m_shopManager;
	float						m_partitionRange;
	CVector3				lightDir = CVector3::Zero;
	float time = 0.0f;
};