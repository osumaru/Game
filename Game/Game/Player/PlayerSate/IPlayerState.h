#pragma once
#include "stdafx.h"


class CPlayerStateMachine;

class IPlayerSate	:public IGameObject
{

	virtual void Update() = 0;
};
