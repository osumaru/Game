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

	void Move();


private:
	Vector3 m_position;
	Vector3 m_moveSpeed = Vector3::Zero;
	SkinModel m_skinmodel;
	CharacterController m_characterController;
};

static Player& GetPlayer()
{
	return Player::GetInstance();
}