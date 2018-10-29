#pragma once
#include "stdafx.h"
class CPlayer;

class IPlayerState
{
public:
	virtual ~IPlayerState() {}

	virtual void Init() {}

	virtual void Update() = 0;

	void SetPlayer(CPlayer* player)
	{
		m_pPlayer = player;
	}
protected:
	CPlayer*		m_pPlayer = nullptr;
};
