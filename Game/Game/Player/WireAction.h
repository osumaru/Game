#pragma once
class CPlayer;
class IEnemy;

class CWireAction
{
public:
	/*
	初期化
	player	プレイヤーのインスタンス
	*/
	void Init(const CPlayer* player);

	/*
	ワイヤー飛ばす先の地点登録
	model	マップに配置してるオブジェクトのモデル
	*/
	void Add(const CSkinModel& model);

	void Update();

	//ワイヤー移動しているか
	bool IsWireMove() const
	{
		return m_isWireMove;
	}

	//ワイヤー移動しているかを設定
	void SetIsWireMove(bool isWireMove)
	{
		m_isWireMove = isWireMove;
	}

	//飛ぶ先の座標を取得。
	const CVector3& GetWirePosition() const
	{
		return m_wirePosition;
	}

	//ワイヤーを使ってどこに飛ぶかの状態
	enum EnWireState
	{
		enStateEnemy,		//飛ぶ先がエネミ―である時
		enStateMap,			//飛ぶ先がマップのオブジェクトであるとき
		enWireStateNum		//
	};

	//ワイヤーの状態を設定
	void SetState(EnWireState state)
	{
		m_state = state;
	}

	//ワイヤーの状態を取得
	EnWireState GetState()
	{
		return m_state;
	}

	//ワイヤーに当たったエネミーを取得
	IEnemy* GetHitEnemy()
	{
		return m_hitEnemy;
	}

	//ワイヤーを飛ばす先のY方向の補正値を取得
	float GetOffsetY()
	{
		return WIRE_OFFSET_Y;
	}

private:
	struct SWireInfo
	{
		float value;
		CVector3 wirePos;
	};

private:
	const CPlayer*					m_pPlayer = nullptr;					//プレイヤーのインスタンス
	IEnemy*							m_hitEnemy = nullptr;					//ワイヤーを当てたエネミー
	bool							m_isWireMove = false;					//ワイヤー移動できるか
	CRayTest						m_wireCollisionSolver;					//ワイヤー移動のコリジョン処理クラス
	CVector3						m_wirePosition;
	static const int				WIRE_POS_LIST_NUM = 10;
	SWireInfo						m_wirePositionList[WIRE_POS_LIST_NUM];							//ワイヤー移動先の座標
	std::vector<const CVector3*>	m_posWireFly;							//飛ぶ先の地点リスト
	EnWireState						m_state = enStateEnemy/*enStateMap*/;					//ワイヤーの状態
	float							WIRE_OFFSET_Y = 0.0f;					//ワイヤーを飛ばす先のY方向の補正値
};