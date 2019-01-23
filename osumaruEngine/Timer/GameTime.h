#pragma once
#include "StopWatch.h"
class CFont;
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
	void Init();
	

	//インスタンスを取得
	static CGameTime& GetInstance()
	{
		static CGameTime gametime;
		return gametime;
	}

	//1フレームの経過時間を取得 
	float GetDeltaFrameTime() const
	{
		return m_gameDeltaTime;
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

	/*
	時間をスローにする設定
	slowTime	スローになっている時間
	slowScale	どのくらいスローにするかの倍率(1.0が等速
	delayTime	スローになるまでの遅延時間
	*/
	void SetSlowDelayTime(float slowTime, float slowScale, float delayTime)
	{
		SetSlow(slowTime, slowScale);
		m_slowDelayTime = delayTime;
	}

	/*
	時間をスローにする設定
	slowTime	スローになっているフレーム数
	slowScale	どのくらいスローにするかの倍率(1.0が等速
	delayTime	スローになるまでの遅延時間
	*/
	void SetSlowDelayTime(int slowCount, float slowScale, float delayTime)
	{
		SetSlow(slowCount, slowScale);
		m_slowDelayTime = delayTime;
	}

	/*
	時間をスローにする設定
	slowTime	スローになっている時間
	slowScale	どのくらいスローにするかの倍率(1.0が等速
	delayCount	スローになるまでの遅延するフレーム数
	*/
	void SetSlowDelayCount(float slowTime, float slowScale, int delayCount)
	{
		SetSlow(slowTime, slowScale);
		m_slowDelayCount = delayCount;
	}

	/*
	時間をスローにする設定
	slowTime	スローになっているフレーム数
	slowScale	どのくらいスローにするかの倍率(1.0が等速
	delayTime	スローになるまでの遅延するフレーム数
	*/
	void SetSlowDelayCount(int slowCount, float slowScale, int delayCount)
	{
		SetSlow(slowCount, slowScale);
		m_slowDelayCount = delayCount;
	}

	//FPSを表示
	void Draw();

	//スローから戻す時のフェード時間を設定
	void SetFadeOutTime(float fadeOutTime)
	{
		m_fadeOutTime = fadeOutTime;
		m_fadeOutTimeMax = fadeOutTime;
	}

	//通常時からスローに入る時のフェード時間を設定
	void SetFadeInTime(float fadeInTime)
	{
		m_fadeInTime = fadeInTime;
		m_fadeInTimeMax = fadeInTime;
	}

private:
	friend class CShakeCamera;
	float		m_slowScale = 0.0f;		//どのぐらいスローにしているかの倍率(1.0が等速
	float		m_slowTime = 0.0f;		//スローになっている間の時間
	int			m_slowCount = 0;		//スローになっている間のフレーム数
	float		m_gameDeltaTime;		//ゲームの中の時間での1フレームの経過時間
	float		m_frameDeltaTime;		//1フレームの経過時間
	float		m_slowDelayTime = 0.0f;	//スローにするまでの遅延時間
	int			m_slowDelayCount = 0;	//スローにするまでのフレーム数
	float		m_fadeInTime = 0.0f;	//普通の時間からスローになるまでフェードさせる間の時間
	float		m_fadeInTimeMax = 0.0f;
	float		m_fadeOutTime = 0.0f;	//スローから普通の時間になるまでフェードさせる間の時間
	float		m_fadeOutTimeMax = 0.0f;	//スローから普通の時間になるまでフェードさせる間の時間
	CFont*		m_font;					//FPS表示させるための文字
};

//ゲームタイマーを取得
static CGameTime& GameTime()
{
	return CGameTime::GetInstance();
}