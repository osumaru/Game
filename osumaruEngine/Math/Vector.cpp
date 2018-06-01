#include "engineStdafx.h"
#include "Vector.h"


const Vector4 Vector4::White = { 1.0f, 1.0f, 1.0f, 1.0f };
const Vector4 Vector4::Black = { 0.0f, 0.0f, 0.0f, 1.0f };
const Vector4 Vector4::Yellow = { 1.0f, 1.0f, 0.0f, 1.0f };

const Vector2 Vector2::Zero = { 0.0f,  0.0f };
const Vector3 Vector3::Zero = { 0.0f,  0.0f,  0.0f };
const Vector3 Vector3::Right = { 1.0f,  0.0f,  0.0f };
const Vector3 Vector3::Left = { -1.0f,  0.0f,  0.0f };
const Vector3 Vector3::Up = { 0.0f,  1.0f,  0.0f };
const Vector3 Vector3::Down = { 0.0f, -1.0f,  0.0f };
const Vector3 Vector3::Front = { 0.0f,   0.0f,  1.0f };
const Vector3 Vector3::Back = { 0.0f,   0.0f, -1.0f };

const Vector3 Vector3::AxisX = { 1.0f,  0.0f,  0.0f };
const Vector3 Vector3::AxisY = { 0.0f,  1.0f,  0.0f };
const Vector3 Vector3::AxisZ = { 0.0f,  0.0f,  1.0f };
const Vector3 Vector3::One = { 1.0f, 1.0f, 1.0f };
const Quaternion Quaternion::Identity = { 0.0f,  0.0f, 0.0f, 1.0f };

/*!
*@brief	�s�񂩂�N�H�[�^�j�I�����쐬�B
*/
void Quaternion::SetRotation(const Matrix& m)
{
	DirectX::XMStoreFloat4(&vec, DirectX::XMQuaternionRotationMatrix(m));
}