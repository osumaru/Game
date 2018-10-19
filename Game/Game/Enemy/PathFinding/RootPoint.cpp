#include "stdafx.h"
#include "RootPoint.h"

void CRootPoint::Init(CVector3 position, int listNumber)
{
	m_position = position;
	m_listNumber = listNumber;
}

bool CRootPoint::Start()
{
	return true;
}

void CRootPoint::Update()
{
}
