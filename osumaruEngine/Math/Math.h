#pragma once
class Math {
public:
	static constexpr float PI = 3.14159265358979323846f;
	static constexpr float PI2 = PI * 2.0f;
	/*!
	* @brief	degreeからradianに変換。
	*/
	constexpr static inline float DegToRad(float deg)
	{
		return deg * (PI / 180.0f);
	}
	/*!
	* @brief	radianからdegreeに変換。
	*/
	constexpr static inline float RadToDeg(float rad)
	{
		return rad / (PI / 180.0f);
	}
	/*!
	*@brief	t0とt1間を線形補完。
	*@details
	*  ret = t0 + (t1-t0) + rate;
	*@param[in]	t		補間率	0.0～1.0
	*/
	constexpr static inline float Lerp(float rate, float t0, float t1)
	{
		return t0 + (t1 - t0)*rate;
	}
};