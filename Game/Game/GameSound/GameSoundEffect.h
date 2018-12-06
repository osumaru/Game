#pragma once
class CGameSoundEffect	: public IGameObject
{
public:
	CGameSoundEffect();
	~CGameSoundEffect();
	bool Start();
	void Update();

private:

	CSoundSource	m_soundEffect;
};

