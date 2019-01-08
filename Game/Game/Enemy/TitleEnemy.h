/*
*	タイトルシーンにだすエネミークラス
*/

#pragma once

class CTitleEnemy : public IGameObject
{
public:
	//初期化
	//modelData		モデルの名前
	//position		座標
	void Init(const wchar_t* modelName, CVector3 position);

	//更新
	void Update() override;

	//描画
	void Draw() override;
private:
	CSkinModel	m_skinModel;	//モデル
	CAnimation	m_animation;	//アニメーション
	CVector3	m_position;		//座標
	CQuaternion m_rotation;		//回転
};