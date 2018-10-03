#include "engineStdafx.h"
#include "Vector.h"
#include "Matrix.h"

const CVector4 CVector4::White = { 1.0f, 1.0f, 1.0f, 1.0f };
const CVector4 CVector4::Black = { 0.0f, 0.0f, 0.0f, 1.0f };
const CVector4 CVector4::Yellow = { 1.0f, 1.0f, 0.0f, 1.0f };

const CVector2 CVector2::Zero = { 0.0f,  0.0f };
const CVector3 CVector3::Zero = { 0.0f,  0.0f,  0.0f };
const CVector3 CVector3::Right = { 1.0f,  0.0f,  0.0f };
const CVector3 CVector3::Left = { -1.0f,  0.0f,  0.0f };
const CVector3 CVector3::Up = { 0.0f,  1.0f,  0.0f };
const CVector3 CVector3::Down = { 0.0f, -1.0f,  0.0f };
const CVector3 CVector3::Front = { 0.0f,   0.0f,  1.0f };
const CVector3 CVector3::Back = { 0.0f,   0.0f, -1.0f };

const CVector3 CVector3::AxisX = { 1.0f,  0.0f,  0.0f };
const CVector3 CVector3::AxisY = { 0.0f,  1.0f,  0.0f };
const CVector3 CVector3::AxisZ = { 0.0f,  0.0f,  1.0f };
const CVector3 CVector3::One = { 1.0f, 1.0f, 1.0f };
const CQuaternion CQuaternion::Identity = { 0.0f,  0.0f, 0.0f, 1.0f };

/*!
*@brief	行列からクォータニオンを作成。
*/
void CQuaternion::SetRotation(const CMatrix& m)
{
	DirectX::XMStoreFloat4(&vec, DirectX::XMQuaternionRotationMatrix(m));
}

/*
*@brief 行列をかける
*/
void CVector3::Mul(CMatrix& mat) const
{
	DirectX::XMStoreFloat3(
		const_cast<DirectX::XMFLOAT3*>(&vec),
		DirectX::XMVector3Transform(*this, DirectX::XMLoadFloat4x4(&mat.mat))
	);
}

/*
*@brief		行列をかける
*/
void CVector4::Mul(CMatrix& mat) const
{
	DirectX::XMStoreFloat4(
		const_cast<DirectX::XMFLOAT4*>(&vec),
		DirectX::XMVector4Transform(*this, mat)
	);
}