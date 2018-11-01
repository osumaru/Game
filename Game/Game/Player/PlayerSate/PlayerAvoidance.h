#pragma once
#include "PlayerState.h"

class CPlayerAvoidance: public IPlayerState
{
public:
	void Init()override;

	void Update()override;
private:
	const CMatrix* m_pBoneMat;
	CVector3 m_manipVec;
	CVector3 m_preBonePos;
};

