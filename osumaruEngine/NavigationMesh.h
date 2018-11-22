#pragma once
class CSkinModel;
//ナビゲーションメッシュのメッシュデータを管理するクラス

class CNavigationMesh : Uncopyable
{
public:
	static const int AREA_NUM = 64;
	//メッシュ情報
	struct SPoligonInfo
	{
		CVector3 position;			//ポリゴンの座標
		CVector3 vertexPos[3];		//ポリゴンの3頂点の座標
	};

	/*
	初期化
	model	メッシュデータとして利用するモデルのデータ
	*/
	void Init(CSkinModel* model);

	typedef std::vector<SPoligonInfo>(*VectorArray)[AREA_NUM];
	
	/*
	メッシュデータの取得
	*/
	VectorArray GetMeshData()
	{
		return m_meshData;
	}


private:
	std::vector<SPoligonInfo> m_meshData[AREA_NUM][AREA_NUM];		//メッシュデータ
};