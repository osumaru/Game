#pragma once
#include "stdafx.h"


class CPlayerStateMachine;

class IPlayerState	:public IGameObject
{

	virtual void Update() = 0;
};
