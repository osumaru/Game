#pragma once
class MapChip;
class IEnemy;
class Player;
class CEnemyGroup;
class INpcState;
//�}�b�v�`�b�v�̃^�O
enum EnMapChipTag
{
	enMapTagUntagged,		//�^�O�Ȃ�
	enMapTagPlayer,			//�v���C���[�^�O
	enMapTagZombie,			//Zombie�^�O
	enMapTagSamurai,		//Samurai�^�O
	enMapTagNinja,			//NInja�^�O
	enMapTagWarrok,			//Warrok�^�O
	enMapTagMaw,			//Maw�^�O
	enMapTagEnemyGroup,		//�G�l�~�[�O���[�v�̃^�O
	enMapTagMapChip,		//�}�b�v�`�b�v
	enMapTagTerrain,		//�n�`�p�̃^�O
	enMapTagShopNpc,		//�XNPC�p�̃^�O
	enMapTagBreakBrock,		//������I�u�W�F�N�g�̃^�O
	enMapTagNum,			//�^�O�̐�
};

struct SMapChipInfo
{
	wchar_t*		m_modelName;	//���f����
	CVector3		m_position;		//���W
	CQuaternion		m_rotation;		//��]
	EnMapChipTag	m_tag;			//�^�O
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
	std::list<IEnemy*> GetEnemyList()
	{
		return m_enemyList;
	}

private:
	std::list<MapChip*>			m_mapChip;				//�}�b�v�`�b�v
	std::list<IEnemy*>			m_enemyList;			//�G�l�~�[���X�g
	std::vector<CEnemyGroup*>	m_enemyGroupList;		//�G�l�~�[�O���[�v�̃x�N�^�[
	bool						m_collider = false;		//AABB���쐬���邩�ǂ���
	std::list<INpcState*>		m_npcList;				//NPC�̃��X�g
};
