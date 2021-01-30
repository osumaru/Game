#pragma once
#include "stdafx.h"
#include "../PlayerGetter.h"


class CPlayer;
//プレイヤーのステートの基底クラス

class IPlayerState
{
public:

	virtual ~IPlayerState() {}

	//初期化関数(ステートが変わったときすぐに呼び出される関数
	virtual void Init() 
	{
		m_isStateTransition = false;
	}
	
	//更新
	virtual void Update() = 0;

	

	//プレイヤーのインスタンスを設定
	void SetPlayer(CPlayer* player, CPlayerGetter* playerGetter)
	{
		m_pPlayer = player;
		m_pPlayerGetter = playerGetter;
	}

	bool GetIsStateTransition() const
	{
		return m_isStateTransition;
	}

protected:
	bool			m_isStateTransition = true;	//ステートが遷移可能か
	CPlayer*		m_pPlayer = nullptr;	//プレイヤーのインスタンス
	CPlayerGetter*	m_pPlayerGetter = nullptr;
};
