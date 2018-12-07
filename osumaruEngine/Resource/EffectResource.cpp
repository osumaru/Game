#include "EffectResource.h"

Effekseer::Effect* CEffectResource::Load(const wchar_t* filePath)
{
	int hash = MakeHash(filePath);
	auto it = m_effects.find(hash);
	if (it == m_effects.end())
	{
		Effekseer::Effect* effect = Effekseer::Effect::Create(Engine().GetEffectEngine().GetEffectManager(), (EFK_CHAR*)filePath);
		m_effects.insert({ hash, effect });
		return effect;
	}
	else
	{
		return it->second;
	}
}