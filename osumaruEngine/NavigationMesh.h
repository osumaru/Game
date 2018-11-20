#pragma once
class CSkinModel;
//ナビゲーションメッシュのメッシュデータを管理するクラス

class CNavigationMesh : Uncopyable
{
public:
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
	
	/*
	メッシュデータの取得
	*/
	const std::vector<SPoligonInfo>* GetMeshData() const
	{
		return m_meshData;
	}


	static const int AREA_NUM = 32;
private:
	std::vector<SPoligonInfo> m_meshData[AREA_NUM * AREA_NUM + AREA_NUM];		//メッシュデータ
};