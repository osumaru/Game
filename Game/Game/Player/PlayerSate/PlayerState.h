#pragma once

class IPlayerState
{
public:

	virtual ~IPlayerState() {}

	virtual void Init() {}
	virtual void Update() = 0;
};
