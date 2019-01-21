#pragma once
class CSkinModel;
//�i�r�Q�[�V�������b�V���̃��b�V���f�[�^���Ǘ�����N���X

class CNavigationMesh : Uncopyable
{
public:
	static const int AREA_NUM = 64;
	//���b�V�����
	struct SPoligonInfo
	{
		CVector3 position;			//�|���S���̍��W
		CVector3 vertexPos[3];		//�|���S����3���_�̍��W
	};

	/*
	������
	model	���b�V���f�[�^�Ƃ��ė��p���郂�f���̃f�[�^
	*/
	void Init();

	typedef std::vector<SPoligonInfo>(*VectorArray)[AREA_NUM];
	
	/*
	���b�V���f�[�^�̎擾
	*/
	VectorArray GetMeshData()
	{
		return m_meshData;
	}

	void SetSkinModel(const CSkinModel* model)
	{
		m_pModel = model;
	}

	struct SObstacleInfo
	{
		CVector3 aabbMin;
		CVector3 center;
		CVector3 aabbMax;
	};

	void AddObstacleObject(SObstacleInfo& info)
	{
		m_obstacleObjects.push_back(info);
	}

	void Draw();
private:
	std::vector<SPoligonInfo>	m_meshData[AREA_NUM][AREA_NUM];		//���b�V���f�[�^
	const CSkinModel*			m_pModel;
	std::list<SObstacleInfo>	m_obstacleObjects;
};