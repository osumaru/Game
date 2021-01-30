#pragma once
class CPlayer;

class Command
{
public:
	Command()
	{

	}
	Command(CPlayer* player)
	{
		m_player = player;
	}

	virtual ~Command()
	{

	}

	virtual void Execute() = 0;
protected:
	CPlayer* m_player;
};

class StandCommand : public Command
{
public:
	StandCommand(CPlayer* player)
	{
		m_player = player;
	}

	void Execute();
};


class WalkCommand : public Command
{
public:
	WalkCommand(CPlayer* player)
	{
		m_player = player;
	}

	void Execute();
};

class RunCommand : public Command
{
public:
	RunCommand(CPlayer* player)
	{
		m_player = player;
	}

	void Execute();
};

class JumpCommand : public Command
{
public:
	JumpCommand(CPlayer* player)
	{
		m_player = player;
	}

	void Execute()override;
};

class AttackCommand : public Command
{
public:
	AttackCommand(CPlayer* player)
	{
		m_player = player;
	}

	void Execute();
};

class DamageCommand : public Command
{
public:
	DamageCommand(CPlayer* player)
	{
		m_player = player;
	}

	void Execute();
};

class StunCommand : public Command
{
public:
	StunCommand(CPlayer* player)
	{
		m_player = player;
	}

	void Execute()override;
};

class AvoidanceCommand : public Command
{
public:
	AvoidanceCommand(CPlayer* player)
	{
		m_player = player;
	}

	void Execute();
};

class DiedCommand : public Command
{
public:
	DiedCommand(CPlayer* player)
	{
		m_player = player;
	}

	void Execute()override;
};

class WireMoveCommand : public Command
{
public:
	WireMoveCommand(CPlayer* player)
	{
		m_player = player;
	}

	void Execute()override;
};

class WireAttackCommand : public Command
{
public:
	WireAttackCommand(CPlayer* player)
	{
		m_player = player;
	}

	void Execute()override;
};

class ArrowAttackCommand : public Command
{
public:
	ArrowAttackCommand(CPlayer* player)
	{
		m_player = player;
	}

	void Execute()override;
};

class ArrowShootCommand : public Command
{
public:
	ArrowShootCommand(CPlayer* player)
	{
		m_player = player;
	}

	void Execute()override;
};

class SkyCommand : public Command
{
public:
	SkyCommand(CPlayer* player)
	{
		m_player = player;
	}

	void Execute()override;
};

class DownCommand : public Command
{
public:
	DownCommand(CPlayer* player)
	{
		m_player = player;
	}

	void Execute()override;
};
