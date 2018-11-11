#pragma once
class CSkinModel;


class CNavigationMesh : Uncopyable
{
public:
	struct SNaviMesh
	{
		CVector3 position;
		CVector3 vertexPos[3];
	};

	void Init(CSkinModel* model);
	
	std::vector<SNaviMesh>& GetMeshData()
	{
		return m_poligonPos;
	}


private:
	std::vector<SNaviMesh> m_poligonPos;
};