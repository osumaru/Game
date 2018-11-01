#pragma once
#include "stdafx.h"
class CPlayer;
//プレイヤーのステートの基底クラス

class IPlayerState
{
public:

	virtual ~IPlayerState() {}

	//初期化関数(ステートが変わったときすぐに呼び出される関数
	virtual void Init() {}
	
	//更新
	virtual void Update() = 0;

	//プレイヤーのインスタンスを設定
	void SetPlayer(CPlayer* player)
	{
		m_pPlayer = player;
	}
protected:
	CPlayer*		m_pPlayer = nullptr;	//プレイヤーのインスタンス
};
