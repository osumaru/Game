#include "stdafx.h"
#include "PathFinding.h"

CPathFinding g_pathFinding;

CPathFinding::CPathFinding()
{
}

CPathFinding::~CPathFinding()
{
}

void CPathFinding::BuildNodes()
{
	const std::vector<CNavigationMesh::SPoligonInfo>* naviMesh = m_naviMesh.GetMeshData();
	for(int i = 0;i < CNavigationMesh::AREA_NUM;i++)
	{
		m_nodes[i].resize(naviMesh[i].size());
		//メッシュデータからノードリンクを作成
		for (int j = 0; j < naviMesh[i].size(); j++)
		{
			for (int k = 0; k < naviMesh[i].size(); k++)
			{
				//3つの頂点を調査して同じ頂点が2つ以上ある場合隣接するポリゴンなのでノードをリンクさせる
				int indexCount = 0;
				for (int parentVertexIndex = 0; parentVertexIndex < 3; parentVertexIndex++)
				{
					for (int childVertexIndex = 0; childVertexIndex < 3; childVertexIndex++)
					{
						if (naviMesh[i][j].vertexPos[parentVertexIndex].x == naviMesh[i][k].vertexPos[childVertexIndex].x &&
							naviMesh[i][j].vertexPos[parentVertexIndex].y == naviMesh[i][k].vertexPos[childVertexIndex].y &&
							naviMesh[i][j].vertexPos[parentVertexIndex].z == naviMesh[i][k].vertexPos[childVertexIndex].z)
						{
							indexCount++;
						}
					}
				}
				if (2 <= indexCount && i != j)
				{
					m_nodes[i][j].linkNode.push_back(&m_nodes[i][k]);
				}

			}
			m_nodes[i][j].position = naviMesh[i][j].position;
			m_nodes[i][j].moveCost = 0;
		}
	}
}

void CPathFinding::FindRoot(std::vector<CVector3>& root, CVector3 startPos, CVector3 targetPos)
{
	root.clear();
	//初期化
	for(int i = 0;i < CNavigationMesh::AREA_NUM;i++)
	{
		for (auto& node : m_nodes[i])
		{
			node.moveCost = -1;
			node.isDone = false;
			node.parentNode = NULL;

		}
	}
	//開始ノードを取得する
	int startIndex = 0;
	int startAreaNum = 0;
	float minLength = FLT_MAX;
	for(int i = 0;i < CNavigationMesh::AREA_NUM;i++)
	{
		for (int j = 0; j < m_nodes[i].size(); j++) {
			CVector3 distance = m_nodes[i][j].position - startPos;
			float length = distance.Length();
			if (length < minLength) {
				minLength = length;
				startIndex = j;
				startAreaNum = i;
			}
		}
	}
	SNode* startNode = &m_nodes[startAreaNum][startIndex];
	startNode->moveCost = 0;
	while (true) {
		SNode* processNode = NULL;
		//全ノードに対して確認/アップデートを行う
		for (int i = 0; i < m_nodes[startAreaNum].size(); i++) {
			SNode* node = &m_nodes[startAreaNum][i];
			if (node->isDone || node->moveCost < 0) {
				continue;
			}
			//処理中のノードがなければ現在のノード
			if (!processNode) {
				processNode = node;
				continue;
			}
			if (node->moveCost < processNode->moveCost) {
				//さらに安い
				processNode = node;
			}
		}
		//処理中のノードがなくなったら
		if (!processNode) {
			break;
		}
		//調査済みにする
		processNode->isDone = true;
		//隣接しているノードにコストを設定する
		for (int i = 0; i < processNode->linkNode.size(); i++) {
			SNode* node = processNode->linkNode[i];
			if (node == NULL) {
				continue;
			}
			CVector3 distance = processNode->position - node->position;
			float cost = processNode->moveCost + distance.Length();
			bool needsUpdate = (node->moveCost < 0) || (node->moveCost > cost);
			if (needsUpdate) {
				//更新の必要あり
				node->moveCost = cost;
				node->parentNode = processNode;
			}
		}
	}
	//ルートを作る
	int targetIndex = 0;
	minLength = FLT_MAX;
	for (int i = 0; i < m_nodes[startAreaNum].size(); i++) {
		CVector3 distance = m_nodes[startAreaNum][i].position - targetPos;
		float length = distance.Length();
		if (length < minLength) {
			minLength = length;
			targetIndex= i;
		}
	}
	SNode* node = &m_nodes[startAreaNum][targetIndex];

	while (node != startNode) {
		root.push_back(node->position);
		node = node->parentNode;
	}
	std::reverse(root.begin(), root.end());
}
