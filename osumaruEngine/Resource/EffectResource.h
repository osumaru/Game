#pragma once

class CEffectResource : Uncopyable
{
public:

	Effekseer::Effect* Load(const wchar_t* filePath);

private:
	std::map<int, Effekseer::Effect*>	m_effects;
};