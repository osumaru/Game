#pragma once

struct playerStatus
{
	int Strength;			//攻撃力
	int Defense;			//防御力
	int	Health;				//体力
	int Level;				//レベル
	int ExperiencePoint	;	//現在の経験値
	int NextExp;			//レベルアップまでに必要な経験値
	int OldExp;				//現在のレベルアップに必要だった経験値
	int AccumulationExp;	//累積経験値

};

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
	const Vector3 GetPosition()
	{
		return m_position;
	}

	//プレイヤーの移動処理を行う関数
	void Move();

	//プレイヤーの回転を行う関数
	void Rotation();

	//プレイヤーのアニメーションの処理を行う関数
	void AnimationMove();

	//ステータスの計算処理を行う関数
	void StatusCalculation();

	//プレイヤーの経験値量を上げる関数（セットする関数ではないです）
	//引数で倒した敵の経験値量を入れる
	void ExpUP(const int expup)
	{
		m_status.ExperiencePoint += expup;
		m_status.AccumulationExp += expup;
	}

	//プレイヤーのステータスを取得
	const playerStatus& GetStatus()
	{
		return m_status;
	}


	const int GetStrength()
	{
		return m_status.Strength;
	}

	//プレイヤーの装備の変更を行う処理
	void WeaponChange();


private:
	Vector3				m_position;							//座標
	Vector3				m_moveSpeed = Vector3::Zero;		//移動速度
	Quaternion			m_rotation = Quaternion::Identity;	//回転
	SkinModel			m_skinmodel;						//スキンモデル
	CharacterController m_characterController;				//キャラクターコントローラー
	Pad					m_pad;								//パッド
	Animation			m_animation;						//アニメーション
	playerStatus		m_status;							//プレイヤーのステータス
	bool				m_isSlip = false;					//スリップ判定
	float				m_slipSpeed = 8.0f;

};

static Player& GetPlayer()
{
	return Player::GetInstance();
}