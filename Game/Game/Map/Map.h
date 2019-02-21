#pragma once
class CTreasureChest;
class CSea;
class MapChip;
class BreakMapObject;
class IEnemy;
class Player;
class CEnemyGroup;
class CShopManager;
//�}�b�v�`�b�v�̃^�O
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
	enMapTagTerrain,		//�n�`�p�̃^�O
	enMapTagMesh,			//���̂����b�V���ɂ��邽�߂̃^�O
	enMapTagItemShop,		//�A�C�e���V���b�v�p�̃^�O
	enMapTagWeaponShop,		//���퉮�p�̃^�O
	enMapTagNormalShop,		//������Ȃ��X�̃��f���̂��߂̃^�O
	enMapTagSoundPoint,		//BGM�p�̃^�O
	enMapTagTree,			//�؂̃��f���ɒ�����^�O
	enMapTagTreasureBox,	//�󔠗p�̃^�O
	enMapTagSea,			//����
	enMapTagCastle,			//Castle�n�̃��f���̃^�O(Z�A�b�v�Ńi�r�Q�[�V�������b�V������p�X����菜���ׂ̂̃��f��
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

//�}�b�v�̃I�u�W�F�N�g��z�u����N���X

class Map : public IGameObject
{
public:
	//�R���X�g���N�^
	Map();

	//�f�X�g���N�^
	~Map();

	//������
	void Init(int stageNum);


	//�X�V�֐�
	void Update()override;

	//���ʑO�Ɉ�x�����Ă΂��
	void BeforeDead()override;

	
	/*
	�}�b�v�`�b�v���f���[�g
	iterator	�f���[�g����}�b�v�`�b�v�̃C�e���[�^�[
	*/
	void MapChipErase(std::list<MapChip*>::iterator iterator, int areaPosX, int areaPosY);



	//�G�l�~�[�O���[�v�̃��X�g���擾
	std::list<CEnemyGroup*>& GetEnemyGroupList()
	{
		return m_enemyGroupList;
	}

	CShopManager* GetShop()
	{
		return m_shopManager;
	}

	

	//�}�b�v�̃I�u�W�F�N�g�ɃA�N�e�B�u�t���O��ݒ�
	void SetIsMapChipActive(bool isActive);

	//�}�b�v�̃I�u�W�F�N�g�̃A�b�v�f�[�g�̃A�N�e�B�u�t���O��ݒ�
	void SetIsMapChipActiveUpdate(bool isActive);

	
	static const int AREA_PARTITION_NUM = 10;

	float GetPartitionRange() const
	{
		return m_partitionRange;
	}

	int GetAreaPosX(const CVector3& position)
	{
		int areaPosX = position.x;
		areaPosX += m_partitionRange * AREA_PARTITION_NUM * 0.5f;
		areaPosX /= m_partitionRange;
		return areaPosX;
	}

	int GetAreaPosY(const CVector3& position)
	{
		int areaPosY = position.z;
		areaPosY += m_partitionRange * AREA_PARTITION_NUM * 0.5f;
		areaPosY /= m_partitionRange;
		return areaPosY;
	}

	std::list<MapChip*>& GetMapChips(int areaPosX, int areaPosY)
	{
		return m_mapChips[areaPosX][areaPosY];
	}



private:
	int						m_playerAreaPosX = 0;
	int						m_playerAreaPosY = 0;
	std::list<MapChip*>		m_mapChips[AREA_PARTITION_NUM][AREA_PARTITION_NUM];
	MapChip*				m_ground = nullptr;
	std::list<CEnemyGroup*>		m_enemyGroupList;		//�G�l�~�[�O���[�v�̃��X�g
	//std::list<CTreasureChest*>	m_treasureList;			//�󔠃��X�g`
	CShopManager*				m_shopManager;
	float						m_partitionRange;
};