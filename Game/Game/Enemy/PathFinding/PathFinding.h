/*
*	�o�H�T���N���X
*/

#pragma once

#include "MapData.h"

class CRootPoint;

#define LINK_NODE_MAX 4		//�אڃm�[�h�̍ő吔
struct SNode {
	SNode*		linkNode[LINK_NODE_MAX];	//�אڃm�[�h�BNULL�ł���Ηאڃm�[�h�Ȃ��B
	SNode*		parentNode;					//�e�̃m�[�h
	CVector2	position;					//�m�[�h�̍��W
	int			moveCost;					//�ړ��R�X�g
	bool		isDone;						//�����ς݃t���O
};

class CPathFinding {
public:
	CPathFinding();
	~CPathFinding();
	//�m�[�h�̍\�z
	void BuildNodes(std::vector<CRootPoint*> rootPoint);
	//���[�g�̌���
	//root			���[�g�̍��W���i�[���郊�X�g
	//startNumber	�X�^�[�g�̃|�C���g�̔ԍ�		
	//targetNumber	�S�[���̃|�C���g�̔ԍ�
	void FindRoot(std::vector<CVector2>& root, int startNumber, int targetNumber);
private:
	SNode m_nodes[MAP_HEIGHT][MAP_WIDTH];	//�m�[�h�̔z��
};

extern CPathFinding g_pathFinding;