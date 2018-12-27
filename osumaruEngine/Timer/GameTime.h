#pragma once
#include "StopWatch.h"

class CGameTime
{
	//コンストラクタ
	CGameTime() :
		m_frameDeltaTime(1.0f / 60.0f)
	{
	}

	//デストラクタ
	~CGameTime()
	{

	}
public:

	//インスタンスを取得
	static CGameTime& GetInstance()
	{
		static CGameTime gametime;
		return gametime;
	}

	//1フレームの経過時間を取得 
	float GetDeltaFrameTime() const
	{
		return m_frameDeltaTime;
	}


	void Update(CStopWatch& sw);

	/*
	時間をスローにする設定
	slowTime	スローになっている時間
	slowScale	どのくらいスローにするかの倍率(1.0が等速
	*/
	void SetSlow(float slowTime, float slowScale)
	{
		m_slowTime = slowTime;
		m_slowScale = slowScale;
	}

	/*
時間をスローにする設定
slowTime	スローになっているフレーム数
slowScale	どのくらいスローにするかの倍率(1.0が等速
*/
	void SetSlow(int slowCount, float slowScale)
	{
		m_slowCount = slowCount;
		m_slowScale = slowScale;
	}

private:
	float		m_slowScale = 0.0f;		//どのぐらいスローにしているかの倍率(1.0が等速
	float		m_slowTime = 0.0f;		//スローになっている間の時間
	int			m_slowCount = 0;
	float		m_frameDeltaTime;		//1フレームの経過時間
};

//ゲームタイマーを取得
static CGameTime& GameTime()
{
	return CGameTime::GetInstance();
}