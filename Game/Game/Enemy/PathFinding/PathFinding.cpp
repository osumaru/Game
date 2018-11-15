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
	const std::vector<CNavigationMesh::SPoligonInfo>& naviMesh = m_naviMesh.GetMeshData();
	m_nodes.resize(naviMesh.size());
	//メッシュデータからノードリンクを作成
	for (int i = 0; i < naviMesh.size(); i++)
	{
		for (int j = 0; j < naviMesh.size(); j++)
		{
			//3つの頂点を調査して同じ頂点が2つ以上ある場合隣接するポリゴンなのでノードをリンクさせる
			int indexCount = 0;
			for (int parentVertexIndex = 0; parentVertexIndex < 3; parentVertexIndex++)
			{
				for (int childVertexIndex = 0; childVertexIndex < 3; childVertexIndex++)
				{
					if (naviMesh[i].vertexPos[parentVertexIndex].x == naviMesh[j].vertexPos[childVertexIndex].x &&
						naviMesh[i].vertexPos[parentVertexIndex].y == naviMesh[j].vertexPos[childVertexIndex].y &&
						naviMesh[i].vertexPos[parentVertexIndex].z == naviMesh[j].vertexPos[childVertexIndex].z)
					{
						indexCount++;
					}
				}
			}
			if (2 <= indexCount && i != j)
			{
				m_nodes[i].linkNode.push_back(&m_nodes[j]);
			}

		}
		m_nodes[i].position = naviMesh[i].position;
		m_nodes[i].moveCost = 0;
	}
}

void CPathFinding::FindRoot(std::vector<CVector3>& root, CVector3 startPos, CVector3 targetPos)
{
	root.clear();
	//初期化
	for (auto& node : m_nodes)
	{
		node.moveCost = -1;
		node.isDone = false;
		node.parentNode = NULL;

	}
	//開始ノードを取得する
	int startIndex = 0;
	float minLength = FLT_MAX;
	for (int i = 0; i < m_nodes.size(); i++) {
		CVector3 distance = m_nodes[i].position - startPos;
		float length = distance.Length();
		if (length < minLength) {
			minLength = length;
			startIndex = i;
		}
	}
	SNode* startNode = &m_nodes[startIndex];
	startNode->moveCost = 0;
	while (true) {
		SNode* processNode = NULL;
		//全ノードに対して確認/アップデートを行う
		for (int i = 0; i < m_nodes.size(); i++) {
			SNode* node = &m_nodes[i];
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
	for (int i = 0; i < m_nodes.size(); i++) {
		CVector3 distance = m_nodes[i].position - targetPos;
		float length = distance.Length();
		if (length < minLength) {
			minLength = length;
			targetIndex= i;
		}
	}
	SNode* node = &m_nodes[targetIndex];

	while (node != startNode) {
		root.push_back(node->position);
		node = node->parentNode;
	}
	std::reverse(root.begin(), root.end());
}
