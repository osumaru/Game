#pragma once

class Player : public GameObject
{
public:


	void Init(Vector3 position);

	static Player& GetInstance()
	{
		static Player player;
		return player;
	}

	void Update()override;

	void Draw()override;

	Vector3 GetPosition()
	{
		return m_position;
	}



private:
	Vector3 m_position;
	SkinModel m_skinmodel;
};

static Player& GetPlayer()
{
	return Player::GetInstance();
}