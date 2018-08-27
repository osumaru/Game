#pragma once

class Player : public GameObject
{
public:

	//プレイヤーの初期化
	void Init(Vector3 position);

	//プレイヤーのインスタンスの取得
	static Player& GetInstance()
	{
		static Player player;
		return player;
	}

	//プレイヤーの更新関数
	void Update()override;

	//プレイヤーの描画関数
	void Draw()override;

	//プレイヤーの座標を取得する関数
	Vector3 GetPosition()
	{
		return m_position;
	}

	//プレイヤーの移動処理を行う関数
	void Move();

	//プレイヤーの回転を行う関数
	void Rotation();

private:
	Vector3				m_position;							//座標
	Vector3				m_moveSpeed = Vector3::Zero;		//移動速度
	Quaternion			m_rotation = Quaternion::Identity;	//回転
	SkinModel			m_skinmodel;						//スキンモデル
	CharacterController m_characterController;				//キャラクターコントローラー
	Pad					m_pad;			//パッド
	Animation			animation;
};

static Player& GetPlayer()
{
	return Player::GetInstance();
}