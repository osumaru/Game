#pragma once
class MapChip;
class CEnemy;

//マップチップのタグ
enum EnMapChipTag
{
	enMapTagUntagged,
	enMapTagPlayer,
	enMapTagEnemy,
	enMapTagMapChip,
	enMapTagNum,
};

struct MapChipInfo
{
	wchar_t*			m_modelName;
	Vector3		m_position;
	Quaternion	m_rotation;
	EnMapChipTag	m_tag;
};

//マップのオブジェクトを配置するクラス

class Map : public GameObject
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

	std::list<CEnemy*> GetEnemy()
	{
		return enemyList;
	}

private:
	std::list<MapChip*> m_mapChip;					//マップチップ
	std::list<CEnemy*> enemyList;
};
