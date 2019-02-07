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
	enMapTagSoundPoint,		//BGM�p�̃^�O
	enMapTagTree,			//�؂̃��f���ɒ�����^�O
	enMapTagTreasureBox,	//�󔠗p�̃^�O
	enMapTagSea,			//����
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
	void MapChipErase(std::list<MapChip*>::iterator iterator);

	//�G�l�~�[�̃��X�g���擾
	std::list<IEnemy*>& GetEnemyList()
	{
		return m_enemyList;
	}

	//�G�l�~�[�O���[�v�̃��X�g���擾
	std::list<CEnemyGroup*>& GetEnemyGroupList()
	{
		return m_enemyGroupList;
	}

	CShopManager* GetShop()
	{
		return m_shopManager;
	}

private:
	std::list<MapChip*>			m_mapChip;				//�}�b�v�`�b�v
	std::list<IEnemy*>			m_enemyList;			//�G�l�~�[���X�g
	std::list<CEnemyGroup*>		m_enemyGroupList;		//�G�l�~�[�O���[�v�̃��X�g
	std::list<CTreasureChest*>	m_treasureList;			//�󔠃��X�g`
	bool						m_collider = false;		//AABB���쐬���邩�ǂ���
	bool						m_isTree = false;	//�ؗp�̃R���C�_�[�̐ݒ�����邽�߂̃t���O		
	CShopManager*				m_shopManager;
};