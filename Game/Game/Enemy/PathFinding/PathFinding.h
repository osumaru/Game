/*
*	�o�H�T���N���X
*/

#pragma once

#include "MapData.h"


#define LINK_NODE_MAX 4		//�אڃm�[�h�̍ő吔
struct SNode {
	std::vector<SNode*>		linkNode;	//�אڃm�[�h�BNULL�ł���Ηאڃm�[�h�Ȃ��B
	SNode*		parentNode;					//�e�̃m�[�h
	CVector3	position;					//�m�[�h�̍��W
	float			moveCost;					//�ړ��R�X�g
	bool		isDone;						//�����ς݃t���O
};

class CPathFinding {
public:
	CPathFinding();
	~CPathFinding();
	//�m�[�h�̍\�z
	void BuildNodes();
	//���[�g�̌���
	//root			���[�g�̍��W���i�[���郊�X�g
	//startNumber	�X�^�[�g�̃|�C���g�̔ԍ�		
	//targetNumber	�S�[���̃|�C���g�̔ԍ�
	void FindRoot(std::vector<CVector3>& root, CVector3 stratPos, CVector3 targetPos);

	void Init(CSkinModel* model)
	{
		m_naviMesh.Init(model);
	}
private:
	std::vector<SNode>		m_nodes[CNavigationMesh::AREA_NUM];	//�m�[�h�̔z��
	const float m_gridSize = 3.0f;
	CNavigationMesh	m_naviMesh;
};

extern CPathFinding g_pathFinding;