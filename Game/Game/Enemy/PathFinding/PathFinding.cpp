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
	m_naviMesh.Init();
	CNavigationMesh::VectorArray naviMesh = m_naviMesh.GetMeshData();

	//vector�̃T�C�Y���m�[�h�̐��������m�ۂ���
	for (int x = 0; x < CNavigationMesh::AREA_NUM; x++)
	{
		for(int y = 0;y < CNavigationMesh::AREA_NUM;y++)
		{
			m_nodes[x][y].resize(naviMesh[x][y].size());
		}
	}
	for(int indexX = 0; indexX < CNavigationMesh::AREA_NUM; indexX++)
	{
		for(int indexY = 0; indexY < CNavigationMesh::AREA_NUM; indexY++)
		{

			//�G���A���̃m�[�h�𑖍����ăm�[�h�̃����N������
			for (int nodeNum = 0; nodeNum < naviMesh[indexX][indexY].size(); nodeNum++)
			{
				//�O�㍶�E�̃G���A����������
				const int LINK_AREA_NUM = 5;
				int areaTranslations[LINK_AREA_NUM][2] = {
					{0, 0},
					{1, 0},
					{-1, 0},
					{0, 1},
					{0, -1}
				};
				for(int linkAreaNum = 0;linkAreaNum < LINK_AREA_NUM;linkAreaNum++)
				{
					int childIndexX = indexX + areaTranslations[linkAreaNum][0];
					int childIndexY = indexY + areaTranslations[linkAreaNum][1];
					if (childIndexX < 0 || CNavigationMesh::AREA_NUM <= childIndexX ||
						childIndexY < 0 || CNavigationMesh::AREA_NUM <= childIndexY)
					{
						continue;
					}
					for (int childNodeNum = 0; childNodeNum < naviMesh[childIndexX][childIndexY].size(); childNodeNum++)
					{
						//�������W�̒��_���J�E���g����
						int indexCount = 0;
						const int VERTEX_NUM = 3;
						//3�̒��_�����W������ׂē������W�����ׂ�
						for (int parentVertexIndex = 0; parentVertexIndex < VERTEX_NUM; parentVertexIndex++)
						{
							for (int childVertexIndex = 0; childVertexIndex < VERTEX_NUM; childVertexIndex++)
							{
								if (naviMesh[indexX][indexY][nodeNum].vertexPos[parentVertexIndex].x == naviMesh[childIndexX][childIndexY][childNodeNum].vertexPos[childVertexIndex].x &&
									naviMesh[indexX][indexY][nodeNum].vertexPos[parentVertexIndex].y == naviMesh[childIndexX][childIndexY][childNodeNum].vertexPos[childVertexIndex].y &&
									naviMesh[indexX][indexY][nodeNum].vertexPos[parentVertexIndex].z == naviMesh[childIndexX][childIndexY][childNodeNum].vertexPos[childVertexIndex].z)
								{
									indexCount++;
								}
							}
						}

						//�������W�̒��_��2����ꍇ�אڂ���|���S���Ȃ̂Ń����N������
						if (indexCount == 2)
						{
							m_nodes[indexX][indexY][nodeNum].linkNode.push_back(&m_nodes[childIndexX][childIndexY][childNodeNum]);
						}
					}
				}

				m_nodes[indexX][indexY][nodeNum].position = naviMesh[indexX][indexY][nodeNum].position;
			}

		}
	}
}

void CPathFinding::FindRoot(std::vector<CVector3>& root, CVector3 startPos, CVector3 targetPos)
{
	root.clear();
	m_openList.clear();
	//������
	for(int x = 0;x < CNavigationMesh::AREA_NUM;x++)
	{
		for (int y = 0; y < CNavigationMesh::AREA_NUM; y++)
		{
			for (auto& node : m_nodes[x][y])
			{
				node.moveCost = -1.0f;
				node.isDone = false;
				node.parentNode = NULL;
				node.nodeState = enNodeStateNone;
			}
		}
	}
	//�J�n�m�[�h���擾����
	SNode* startNode = nullptr;
	float minLength = FLT_MAX;
	for(int x = 0;x < CNavigationMesh::AREA_NUM;x++)
	{
		for (int y = 0; y < CNavigationMesh::AREA_NUM; y++)
		{
			for (auto& node : m_nodes[x][y]) {
				CVector3 distance = node.position - startPos;
				float length = distance.Length();
				if (length < minLength) {
					minLength = length;
					startNode = &node;
				}
			}
		}
	}
	if (startNode == nullptr) { return; }
	startNode->moveCost = 0.0f;
	SNode* currentNode = startNode;
	//���[�g�����
	SNode* targetNode = nullptr;
	minLength = FLT_MAX;
	for (int x = 0; x < CNavigationMesh::AREA_NUM; x++)
	{
		for (int y = 0; y < CNavigationMesh::AREA_NUM; y++)
		{
			for (auto& node : m_nodes[x][y])
			{
				CVector3 distance = node.position - targetPos;
				float length = distance.Length();
				if (length < minLength)
				{
					minLength = length;
					targetNode = &node;
				}
			}
		}
	}

	//�^�[�Q�b�g�ɂ��ǂ蒅���܂Ōo�H�T��������
	while (targetNode != currentNode)
	{
		currentNode->nodeState = enNodeStateClose;
		//�I�[�v�������m�[�h�̎���̃m�[�h���I�[�v�����Ă���
		for (int i = 0; i < currentNode->linkNode.size(); i++)
		{
			//�m�[�h���܂��I�[�v������Ă��Ȃ���΃��X�g�ɒǉ�
			if (currentNode->linkNode[i]->nodeState == enNodeStateNone)
			{
				currentNode->linkNode[i]->nodeState = enNodeStateOpen;
				m_openList.push_back(currentNode->linkNode[i]);
				currentNode->linkNode[i]->parentNode = currentNode;
				CVector3 distance = currentNode->linkNode[i]->position - targetPos;
				currentNode->linkNode[i]->moveCost = distance.LengthSq();
			}
		}

		float length = FLT_MAX; 
		std::list<SNode*>::iterator it = m_openList.begin();
		std::list<SNode*>::iterator deleteIt = it;
		//�N���[�Y����m�[�h���ړ��R�X�g����v�Z
		while (it != m_openList.end())
		{
			if ((*it)->moveCost < length && 0.0f <= (*it)->moveCost)
			{
				length = (*it)->moveCost;
				deleteIt = it;
			}

			it++;
		}

		currentNode = *deleteIt;
		m_openList.erase(deleteIt);
	}
	SNode* node = targetNode;
	while (node != startNode)
	{
		//�f�o�b�O�p�ɍ��̂�`�悷��p�̃��C���`����g���ă��[�g��`��
		btVector3 nodePos;
		nodePos.setX(node->position.x);
		nodePos.setY(node->position.y);
		nodePos.setZ(node->position.z);
		btVector3 nodeParentPos;
		nodeParentPos.setX(node->parentNode->position.x);
		nodeParentPos.setY(node->parentNode->position.y);
		nodeParentPos.setZ(node->parentNode->position.z);
		PhysicsWorld().GetRigidBodyDraw().drawLine(nodePos, nodeParentPos, btVector3(0.0f, 0.0f, 0.0f));
		//���[�g�ɍ��W��ς�ł���
		root.push_back(node->position);
		node = node->parentNode;
	}
	std::reverse(root.begin(), root.end());
}
