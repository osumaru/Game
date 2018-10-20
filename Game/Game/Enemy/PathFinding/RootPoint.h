/*
*	経路探索用のポイントクラス
*/

#pragma once

class CRootPoint : public IGameObject
{
public:
	//初期化
	//position			座標
	//listNumber		リストの番号
	void Init(CVector3 position, int listNumer);

	//更新する前に一度だけ呼ばれる
	bool Start();

	//更新
	void Update();

	//座標を取得
	const CVector3& GetPosition()
	{
		return m_position;
	}

	//リストに格納されている番号を取得
	int GetListNumber()
	{
		return m_listNumber;
	}

private:
	CVector3 m_position;		//座標
	int      m_listNumber = 0;	//リストに格納されている番号
};