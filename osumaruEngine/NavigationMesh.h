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
	void Init(CSkinModel* model);

	typedef std::vector<SPoligonInfo>(*VectorArray)[AREA_NUM];
	
	/*
	���b�V���f�[�^�̎擾
	*/
	VectorArray GetMeshData()
	{
		return m_meshData;
	}


private:
	std::vector<SPoligonInfo> m_meshData[AREA_NUM][AREA_NUM];		//���b�V���f�[�^
};