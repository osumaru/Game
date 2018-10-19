#include "stdafx.h"
#include "PathFinding.h"
#include "RootPoint.h"

CPathFinding g_pathFinding;

CPathFinding::CPathFinding()
{
}

CPathFinding::~CPathFinding()
{
}

void CPathFinding::BuildNodes(std::vector<CRootPoint*> rootPoint)
{
	for (int y = 0; y < MAP_HEIGHT; y++) {
		for (int x = 0; x < MAP_WIDTH; x++) {
			SNode* node = &m_nodes[y][x];
			//隣接マップをNULL初期化
			node->linkNode[0] = NULL;
			node->linkNode[1] = NULL;
			node->linkNode[2] = NULL;
			node->linkNode[3] = NULL;
			node->moveCost = 0;
			//隣接マップのノードを入れる
			//右のノード
			if (x + 1 < MAP_WIDTH) {
				node->linkNode[0] = &m_nodes[y][x + 1];
			}
			//左のノード
			if (x - 1 >= 0) {
				node->linkNode[1] = &m_nodes[y][x - 1];
			}
			//上のノード
			if (y + 1 < MAP_HEIGHT) {
				node->linkNode[2] = &m_nodes[y + 1][x];
			}
			//下のノード
			if (y - 1 >= 0) {
				node->linkNode[3] = &m_nodes[y - 1][x];
			}
			//座標を設定する
			CVector3 position = rootPoint[x + y * MAP_WIDTH]->GetPosition();
			node->position = { position.x, position.z };
		}
	}
}

void CPathFinding::FindRoot(std::vector<CVector2>& root, int startNumber, int targetNumber)
{
	root.clear();
	//初期化
	for (int y = 0; y < MAP_HEIGHT; y++) {
		for (int x = 0; x < MAP_WIDTH; x++) {
			m_nodes[y][x].moveCost = -1;
			m_nodes[y][x].isDone = false;
			m_nodes[y][x].parentNode = NULL;
		}
	}
	//開始ノードを取得する
	int startY = startNumber / MAP_WIDTH;
	int startX = startNumber - startY * MAP_WIDTH;
	SNode* startNode = &m_nodes[startY][startX];
	startNode->moveCost = 0;
	while (true) {
		SNode* processNode = NULL;
		//全ノードに対して確認/アップデートを行う
		for (int y = 0; y < MAP_HEIGHT; y++) {
			for (int x = 0; x < MAP_WIDTH; x++) {
				SNode* node = &m_nodes[y][x];
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
		}
		//処理中のノードがなくなったら
		if (!processNode) {
			break;
		}
		//調査済みにする
		processNode->isDone = true;
		//隣接しているノードにコストを設定する
		for (int i = 0; i < LINK_NODE_MAX; i++) {
			SNode* node = processNode->linkNode[i];
			if (node == NULL) {
				continue;
			}
			int cost = processNode->moveCost + 1;
			bool needsUpdae = (node->moveCost < 0) || (node->moveCost > cost);
			if (needsUpdae) {
				//更新の必要あり
				node->moveCost = cost;
				node->parentNode = processNode;
			}
		}
	}
	//ルートを作る
	int targetY = targetNumber / MAP_WIDTH;
	int targetX = targetNumber - targetY * MAP_WIDTH;
	SNode* node = &m_nodes[targetY][targetX];

	while (node != startNode) {
		root.push_back(node->position);
		node = node->parentNode;
	}
	std::reverse(root.begin(), root.end());
}
