/*
*	経路探索クラス
*/

#pragma once

#include "MapData.h"

class CRootPoint;

#define LINK_NODE_MAX 4		//隣接ノードの最大数
struct SNode {
	SNode*		linkNode[LINK_NODE_MAX];	//隣接ノード。NULLであれば隣接ノードなし。
	SNode*		parentNode;					//親のノード
	CVector2	position;					//ノードの座標
	int			moveCost;					//移動コスト
	bool		isDone;						//調査済みフラグ
};

class CPathFinding {
public:
	CPathFinding();
	~CPathFinding();
	//ノードの構築
	void BuildNodes(std::vector<CRootPoint*> rootPoint);
	//ルートの検索
	//root			ルートの座標を格納するリスト
	//startNumber	スタートのポイントの番号		
	//targetNumber	ゴールのポイントの番号
	void FindRoot(std::vector<CVector2>& root, int startNumber, int targetNumber);
private:
	SNode m_nodes[MAP_HEIGHT][MAP_WIDTH];	//ノードの配列
};

extern CPathFinding g_pathFinding;