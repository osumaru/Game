#include "engineStdafx.h"
#include "StopWatch.h"


CStopWatch::CStopWatch() :
	m_start(0),
	m_end(0),
	m_frequency(1),
	m_time(0.0f),
	m_millTime(0.0f)
{
}

CStopWatch::~CStopWatch()
{

}

void CStopWatch::Start()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&m_start);
}

void CStopWatch::Stop()
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_frequency);
	QueryPerformanceCounter((LARGE_INTEGER*)&m_end);
	m_time = (double)(m_end - m_start) / m_frequency;
	m_millTime = m_time * 1000.0;
}


