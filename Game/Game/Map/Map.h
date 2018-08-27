#pragma once
class MapChip;
class Player;
//�}�b�v�`�b�v�̃^�O
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

//�}�b�v�̃I�u�W�F�N�g��z�u����N���X

class Map : public GameObject
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

private:
	std::list<MapChip*> m_mapChip;					//�}�b�v�`�b�v
};
