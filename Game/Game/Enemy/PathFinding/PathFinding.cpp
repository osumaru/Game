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
			//�אڃ}�b�v��NULL������
			node->linkNode[0] = NULL;
			node->linkNode[1] = NULL;
			node->linkNode[2] = NULL;
			node->linkNode[3] = NULL;
			node->moveCost = 0;
			//�אڃ}�b�v�̃m�[�h������
			//�E�̃m�[�h
			if (x + 1 < MAP_WIDTH) {
				node->linkNode[0] = &m_nodes[y][x + 1];
			}
			//���̃m�[�h
			if (x - 1 >= 0) {
				node->linkNode[1] = &m_nodes[y][x - 1];
			}
			//��̃m�[�h
			if (y + 1 < MAP_HEIGHT) {
				node->linkNode[2] = &m_nodes[y + 1][x];
			}
			//���̃m�[�h
			if (y - 1 >= 0) {
				node->linkNode[3] = &m_nodes[y - 1][x];
			}
			//���W��ݒ肷��
			CVector3 position = rootPoint[x + y * MAP_WIDTH]->GetPosition();
			node->position = { position.x, position.z };
		}
	}
}

void CPathFinding::FindRoot(std::vector<CVector2>& root, int startNumber, int targetNumber)
{
	root.clear();
	//������
	for (int y = 0; y < MAP_HEIGHT; y++) {
		for (int x = 0; x < MAP_WIDTH; x++) {
			m_nodes[y][x].moveCost = -1;
			m_nodes[y][x].isDone = false;
			m_nodes[y][x].parentNode = NULL;
		}
	}
	//�J�n�m�[�h���擾����
	int startY = startNumber / MAP_WIDTH;
	int startX = startNumber - startY * MAP_WIDTH;
	SNode* startNode = &m_nodes[startY][startX];
	startNode->moveCost = 0;
	while (true) {
		SNode* processNode = NULL;
		//�S�m�[�h�ɑ΂��Ċm�F/�A�b�v�f�[�g���s��
		for (int y = 0; y < MAP_HEIGHT; y++) {
			for (int x = 0; x < MAP_WIDTH; x++) {
				SNode* node = &m_nodes[y][x];
				if (node->isDone || node->moveCost < 0) {
					continue;
				}
				//�������̃m�[�h���Ȃ���Ό��݂̃m�[�h
				if (!processNode) {
					processNode = node;
					continue;
				}
				if (node->moveCost < processNode->moveCost) {
					//����Ɉ���
					processNode = node;
				}
			}
		}
		//�������̃m�[�h���Ȃ��Ȃ�����
		if (!processNode) {
			break;
		}
		//�����ς݂ɂ���
		processNode->isDone = true;
		//�אڂ��Ă���m�[�h�ɃR�X�g��ݒ肷��
		for (int i = 0; i < LINK_NODE_MAX; i++) {
			SNode* node = processNode->linkNode[i];
			if (node == NULL) {
				continue;
			}
			int cost = processNode->moveCost + 1;
			bool needsUpdae = (node->moveCost < 0) || (node->moveCost > cost);
			if (needsUpdae) {
				//�X�V�̕K�v����
				node->moveCost = cost;
				node->parentNode = processNode;
			}
		}
	}
	//���[�g�����
	int targetY = targetNumber / MAP_WIDTH;
	int targetX = targetNumber - targetY * MAP_WIDTH;
	SNode* node = &m_nodes[targetY][targetX];

	while (node != startNode) {
		root.push_back(node->position);
		node = node->parentNode;
	}
	std::reverse(root.begin(), root.end());
}
