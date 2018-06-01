#pragma once

#include "Vector.h"

class Matrix {
public:

	union {
		DirectX::XMFLOAT4X4 mat;
		struct {
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		Vector4 v[4];
		float m[4][4];
	};
	static const Matrix Identity;	//!<単位行列。
public:
	operator DirectX::XMMATRIX() const
	{
		return DirectX::XMLoadFloat4x4(&mat);
	}
	Matrix() {}
	Matrix(float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33) :
		mat(m00, m01, m02, m03,
			m10, m11, m12, m13,
			m20, m21, m22, m23,
			m30, m31, m32, m33)
	{

	}
	Matrix(const DirectX::XMFLOAT4X4& m)
	{
		mat = m;
	}
	/*!
	*@brief	代入演算子。
	*/
	Matrix& operator=(const Matrix& _m)
	{
		mat = _m.mat;
		return *this;
	}
	/*!
	*@brief	ベクトルと3x3行列の乗算
	*@param[in,out]		v	乗算されるベクトル。
	*/
	void Mul3x3(Vector3& vOut) const
	{
		Vector3 vTmp = vOut;
		vOut.x = vTmp.x * m[0][0] + vTmp.y * m[1][0] + vTmp.z * m[2][0];
		vOut.y = vTmp.x * m[0][1] + vTmp.y * m[1][1] + vTmp.z * m[2][1];
		vOut.z = vTmp.x * m[0][2] + vTmp.y * m[1][2] + vTmp.z * m[2][2];
	}

	/*!
	*@brief	ベクトルと行列の乗算
	*@param[in,out]		v	乗算されるベクトル。
	*/
	void Mul(Vector3& vOut) const
	{
		DirectX::XMStoreFloat3(
			&vOut.vec,
			DirectX::XMVector3Transform(vOut, *this)
		);
	}
	void Mul(Vector4& vOut) const
	{
		DirectX::XMStoreFloat4(
			&vOut.vec,
			DirectX::XMVector4Transform(vOut, *this)
		);
	}
	/*!
	*@brief	平行移動行列を作成。
	*/
	void MakeTranslation(const Vector3& trans)
	{
		DirectX::XMStoreFloat4x4(
			&mat,
			DirectX::XMMatrixTranslationFromVector(trans)
		);
	}
	/*!
	*@brief	Y軸周りの回転行列を作成。
	*@param[in]	angle	回転角度(単位ラジアン)
	*/
	void MakeRotationY(float angle)
	{
		DirectX::XMStoreFloat4x4(
			&mat,
			DirectX::XMMatrixRotationY(angle)
		);
	}
	/*!
	*@brief	Z軸周りの回転行列を作成。
	*@param[in]	angle	回転角度(単位ラジアン)
	*/
	void MakeRotationZ(float angle)
	{
		DirectX::XMStoreFloat4x4(
			&mat,
			DirectX::XMMatrixRotationZ(angle)
		);
	}
	/*!
	*@brief	X軸周りの回転行列を作成。
	*@param[in]	angle	回転角度(単位ラジアン)
	*/
	void MakeRotationX(float angle)
	{
		DirectX::XMStoreFloat4x4(
			&mat,
			DirectX::XMMatrixRotationX(angle)
		);
	}
	/*!
	*@brief	クォータニオンから回転行列を作成。
	*@param[in]	q		クォータニオン
	*/
	void MakeRotationFromQuaternion(const Quaternion& q)
	{
		DirectX::XMStoreFloat4x4(
			&mat,
			DirectX::XMMatrixRotationQuaternion(q)
		);
	}
	/*!
	*@brief	任意の軸周りの回転行列を作成。
	*@param[in]	axis	回転軸。
	*@param[in]	angle	回転角度
	*/
	void MakeRotationAxis(const Vector3& axis, float angle)
	{
		DirectX::XMStoreFloat4x4(
			&mat,
			DirectX::XMMatrixRotationAxis(axis, angle)
		);
	}
	/*!
	*@brief	拡大行列を作成。
	*@param[in] scale		拡大率。
	*/
	void MakeScaling(const Vector3& scale)
	{
		DirectX::XMStoreFloat4x4(
			&mat,
			DirectX::XMMatrixScalingFromVector(scale)
		);
	}
	/*!
	* @brief	プロジェクション行列を作成。
	*@param[in]	viewAngle	画角。(ラジアン)。
	*@param[in]	aspect		アスペクト比。
	*@param[in]	fNear		近平面。
	*@param[in]	fFar		遠平面。
	*/
	void MakeProjectionMatrix(
		float viewAngle,
		float aspect,
		float fNear,
		float fFar
	)
	{
		DirectX::XMStoreFloat4x4(
			&mat,
			DirectX::XMMatrixPerspectiveFovLH(viewAngle, aspect, fNear, fFar)
		);
	}
	/*!
	* @brief	平行投影行列を作成。
	*@param[in]	w			ビューボリュームの幅。
	*@param[in]	h			ビューボリュームの高さ。
	*@param[in]	fNear		近平面。
	*@param[in]	fFar		遠平面。
	*/
	void MakeOrthoProjectionMatrix(float w, float h, float fNear, float fFar)
	{
		DirectX::XMStoreFloat4x4(
			&mat,
			DirectX::XMMatrixOrthographicLH(w, h, fNear, fFar)
		);
	}
	/*!
	* @brief	注視点、上方向、カメラ位置からカメラ行列を作成。
	*@param[in]	position	カメラ位置。
	*@param[in]	target		注視点。
	*@param[in]	up			カメラの上方向。
	*/
	void MakeLookAt(const Vector3& position, const Vector3& target, const Vector3& up)
	{
		DirectX::XMStoreFloat4x4(
			&mat,
			DirectX::XMMatrixLookAtLH(position, target, up)
		);
	}
	/*!
	*@brief	行列と行列の乗算
	*@details
	* *this = m0 * m1
	*/
	void Mul(const Matrix& m0, const Matrix& m1)
	{
		DirectX::XMFLOAT4X4 lm;
		DirectX::XMStoreFloat4x4(
			&lm,
			DirectX::XMMatrixMultiply(m0, m1)
		);
		mat = lm;
	}
	/*!
	*@brief	逆行列を計算。
	*@param[in]	m	元になる行列。
	*/
	void Inverse(const Matrix& _m)
	{
		DirectX::XMStoreFloat4x4(
			&mat,
			DirectX::XMMatrixInverse(NULL, _m)
		);
	}
	void Inverse()
	{
		Inverse(*this);
	}
	void Transpose()
	{
		DirectX::XMStoreFloat4x4(
			&mat,
			DirectX::XMMatrixTranspose(*this)
		);
	}

};