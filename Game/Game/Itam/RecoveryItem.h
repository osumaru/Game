/*
*	回復アイテムクラス
*/

#pragma once

class CRecoveryItem : public IGameObject
{
public:
	//初期化
	//position	座標
	void Init(CVector3 position);

	//更新
	void Update();

	//描画
	void Draw();

private:
	CSkinModel m_skinModel;	//スキンモデル
	CVector3 m_position;	//座標
};
