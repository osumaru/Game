/*
*	ウォーロッククラス
*/

#pragma once

#include "Enemy/IEnemy.h"

class CRock;

class CWarrok : public IEnemy
{
public:
	//コンストラクタ
	CWarrok();

	//デストラクタ
	~CWarrok();

	//初期化
	//position	座標
	void Init(CVector3 position) override;

	//更新される前に一度だけ呼ばれる
	bool Start();

	//更新
	void Update();

	//描画
	void Draw();

	//攻撃
	void Attack() override;

	void OnInvokeAnimationEvent(const wchar_t* animClipName, const wchar_t* eventName)override;

private:
	CRock* m_rock = nullptr;	//岩
	//CVector3	m_handPos;	//岩を投げる用の手の座標
	//const CMatrix*	m_leftHandMatrix = nullptr;	//岩を投げる用の手の行列
	const CMatrix*	m_rightHandMatrix = nullptr;	//岩を投げる用の手の行列
};