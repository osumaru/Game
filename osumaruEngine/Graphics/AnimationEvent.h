#pragma once

/*
アニメーションイベント
*/
class CAnimationEvent
{
public:
	CAnimationEvent() :
		m_isInvoked(false),
		m_invokeTime(0.0f),
		m_eventName()
	{

	}
	//イベント発生時間を取得
	float GetInvokeTime() const
	{
		return m_invokeTime;
	}

	//イベント名を取得
	const wchar_t* GetEventName() const
	{
		return m_eventName;
	}

	//イベント名を設定
	void SetEventName(wchar_t* eventName)
	{
		m_eventName = eventName;
	}

	//イベント発生時間を設定
	void SetInvokeTime(float time)
	{
		m_invokeTime = time;
	}

	//イベントが発生済みか判定
	bool IsInvoked() const
	{
		return m_isInvoked;
	}

	//イベントが発生済みのフラグを設定する
	void SetInvokedFlg(bool flg)
	{
		m_isInvoked = flg;
	}
private:
	bool		m_isInvoked;	//イベント発生済み？
	float		m_invokeTime;	//イベント発生時間
	wchar_t*	m_eventName;	//イベント名
};