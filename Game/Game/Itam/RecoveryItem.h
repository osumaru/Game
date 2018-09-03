#pragma once

class CRecoveryItem : public IGameObject
{
public:
	void Init(CVector3 position);

	void Update();

	void Draw();

private:
	CSkinModel m_skinModel;
	CVector3 m_position;
};
